#Requires -Version 7
<#
.SYNOPSIS
  Claude Code の会話履歴（jsonl）から、スレッド（1会話）単位の指標を threads.csv に書く。定義は README.md。

.DESCRIPTION
  - 1ターン = 実プロンプトから、次の実プロンプトの直前までの区間。自走時間の代理指標。
  - ターンの長さは -CapSeconds で打ち切る（離席・許可待ちの放置が混ざるため）。打ち切った件数は capped_turns。
  - 同じ会話 ID が複数のディレクトリにある（rename 時の履歴コピー）ときは、1つにまとめる。
  - threads.csv は派生データ。Claude Code が古い履歴を消しても残るよう、既存の行は、履歴が無い会話では保持する。
  - 会話の本文は読むが、書き出さない（数値と ID だけ）。

.PARAMETER Current
  会話の ID だけを出す（終了処理で sessions.csv の thread_id に書く用）。-Cwd（Claude Code を開いた作業ディレクトリ）を渡すと、そのキーの履歴の中で最新のものを選ぶ。省略または履歴が無いときは、全体で最新の更新（並行セッションがあると外れうる）。選んだ会話の前後 -CurrentWindowMin 分（既定30）以内に別の会話も更新されていたら、警告を出す（出力は ID だけが標準出力。警告は別のストリーム）。

.PARAMETER Cwd
  Claude Code を開いた作業ディレクトリ（セッションの主な作業ディレクトリ。シェルのカレントではない）。

.PARAMETER Report
  threads.csv と sessions.csv から、要約と「無駄の候補」を出す。書き込みはしない。

.EXAMPLE
  pwsh -NoProfile -File docs/metrics/extract-threads.ps1
  pwsh -NoProfile -File docs/metrics/extract-threads.ps1 -Report
#>
[CmdletBinding(PositionalBinding = $false)]
param(
  [string]$ProjectsDir = (Join-Path $HOME '.claude/projects'),
  [string]$Out = (Join-Path $PSScriptRoot 'threads.csv'),
  [string]$Sessions = (Join-Path $PSScriptRoot 'sessions.csv'),
  [int]$CapSeconds = 1800,
  [int]$IdleDays = 3,
  [string]$Since = '2026-10-06',
  [string]$Cwd = '',
  [int]$CurrentWindowMin = 30,
  [switch]$Current,
  [switch]$Report
)

# threads.csv の列。履歴が消えた会話の古い行は、新しい列が空になる（空 = 不明。0 ではない）
$Columns = 'thread_id', 'project_key', 'first_ts', 'last_ts', 'prompts', 'active_min', 'turn_med_s', 'turn_p90_s', 'turn_max_s', 'capped_turns',
  'tools_total', 'tools_per_turn_med', 'tool_errors', 'out_tokens', 'fresh_in_tokens', 'cache_read_tokens', 'ctx_max_tokens',
  'know_reads', 'know_searches', 'know_files', 'kit_files', 'again_hint'

# 「前にも言った」の機械検出（目安。誤検出を含む。本命はユーザーが付ける `again`）
$AgainPattern = '前にも|前に(も)?言っ|さっき(も)?言っ|また同じ|何度(も)?(言|説明)|\bagain\b'

function Get-Pct($sorted, [double]$p) {
  $sorted = @($sorted)
  if ($sorted.Count -eq 0) { return '' }
  $sorted[[math]::Min($sorted.Count - 1, [math]::Ceiling($p * $sorted.Count) - 1)]
}

# 同じ会話 ID のコピーは、works を含むディレクトリのものを優先して1つにする
function Get-ThreadFiles {
  Get-ChildItem -Path $ProjectsDir -Recurse -Filter *.jsonl -File |
    Group-Object BaseName |
    ForEach-Object { $_.Group | Sort-Object { if ($_.Directory.Name -match 'works') { 0 } else { 1 } }, LastWriteTime | Select-Object -First 1 }
}

function Read-Thread($file) {
  $events = [System.Collections.Generic.List[object]]::new()
  $msgs = @{}
  $toolErrors = 0
  $knowFiles = [System.Collections.Generic.SortedSet[string]]::new()
  $kitFiles = [System.Collections.Generic.SortedSet[string]]::new()
  $knowSearches = 0
  $againHint = 0
  foreach ($line in [System.IO.File]::ReadLines($file.FullName)) {
    if (-not $line.Contains('"timestamp"')) { continue }
    try { $o = $line | ConvertFrom-Json } catch { continue }
    if ($o.isSidechain -or $o.type -notin 'user', 'assistant') { continue }
    $ts = [datetime]$o.timestamp
    $real = $false
    $tools = 0
    if ($o.type -eq 'user') {
      $real = -not $o.toolUseResult -and -not $o.isMeta
      if ($real) {
        $txt = if ($o.message.content -is [string]) { $o.message.content } else { @($o.message.content | Where-Object type -eq 'text' | ForEach-Object text) -join ' ' }
        if ($txt -match $AgainPattern) { $againHint++ }
      }
      if ($o.message.content -is [array]) {
        $toolErrors += @($o.message.content | Where-Object { $_.type -eq 'tool_result' -and $_.is_error }).Count
      }
    } else {
      if ($o.message.content -is [array]) {
        $uses = @($o.message.content | Where-Object type -eq 'tool_use')
        $tools = $uses.Count
        foreach ($t in $uses) {
          $in = $t.input
          if ($t.name -eq 'Read' -and $in.file_path) {
            if ($in.file_path -match '[\\/]knowledge[\\/]([^\\/]+\.md)$') { [void]$knowFiles.Add($Matches[1]) }
            elseif ($in.file_path -match '[\\/]workflow-kit[\\/]([^\\/]+\.md)$') { [void]$kitFiles.Add($Matches[1]) }
          } elseif ($t.name -in 'Grep', 'Glob', 'Bash', 'PowerShell') {
            $s = (@($in.pattern, $in.path, $in.command) | Where-Object { $_ }) -join ' '
            if (($s -match 'exmem' -and $s -match 'knowledge') -or $s -match 'find-knowledge') { $knowSearches++ }
          }
        }
      }
      # 1回の応答が複数行に分かれ、同じ message.id と同じ usage が繰り返されるので、id で1つにする
      $u = $o.message.usage
      if ($o.message.id -and $u) {
        $msgs[$o.message.id] = [pscustomobject]@{
          out = [long]$u.output_tokens
          fresh = [long]$u.input_tokens + [long]$u.cache_creation_input_tokens
          cacheRead = [long]$u.cache_read_input_tokens
        }
        $ctx = [long]$u.input_tokens + [long]$u.cache_creation_input_tokens + [long]$u.cache_read_input_tokens
        $msgs[$o.message.id] | Add-Member ctx $ctx
      }
    }
    $events.Add([pscustomobject]@{ t = $ts; real = $real; tools = $tools })
  }
  if ($events.Count -eq 0) { return $null }
  $events = @($events | Sort-Object t)

  $turns = [System.Collections.Generic.List[object]]::new()
  $cur = $null
  foreach ($e in $events) {
    if ($e.real) {
      if ($cur) { $turns.Add($cur) }
      $cur = [pscustomobject]@{ s = $e.t; e = $e.t; tools = 0 }
    } elseif ($cur) {
      $cur.e = $e.t
      $cur.tools += $e.tools
    }
  }
  if ($cur) { $turns.Add($cur) }

  $spans = @($turns | ForEach-Object { ($_.e - $_.s).TotalSeconds })
  $capped = @($spans | Where-Object { $_ -gt $CapSeconds }).Count
  $used = @($spans | ForEach-Object { [math]::Min($_, $CapSeconds) } | Sort-Object)
  $toolsPer = @($turns | ForEach-Object tools | Sort-Object)
  $m = @($msgs.Values)
  [pscustomobject][ordered]@{
    thread_id        = $file.BaseName
    project_key      = $file.Directory.Name -replace '^C--vault-(repos-github-com-yuzucha16-)?', ''
    first_ts         = $events[0].t.ToUniversalTime().ToString('yyyy-MM-ddTHH:mm:ssZ')
    last_ts          = $events[-1].t.ToUniversalTime().ToString('yyyy-MM-ddTHH:mm:ssZ')
    prompts          = $turns.Count
    active_min       = [math]::Round(($used | Measure-Object -Sum).Sum / 60, 1)
    turn_med_s       = [math]::Round((Get-Pct $used 0.5))
    turn_p90_s       = [math]::Round((Get-Pct $used 0.9))
    turn_max_s       = [math]::Round(($used | Select-Object -Last 1))
    capped_turns     = $capped
    tools_total      = ($toolsPer | Measure-Object -Sum).Sum
    tools_per_turn_med = Get-Pct $toolsPer 0.5
    tool_errors      = $toolErrors
    out_tokens       = ($m | Measure-Object out -Sum).Sum
    fresh_in_tokens  = ($m | Measure-Object fresh -Sum).Sum
    cache_read_tokens = ($m | Measure-Object cacheRead -Sum).Sum
    ctx_max_tokens   = ($m | Measure-Object ctx -Maximum).Maximum
    know_reads       = $knowFiles.Count
    know_searches    = $knowSearches
    know_files       = $knowFiles -join ';'
    kit_files        = $kitFiles -join ';'
    again_hint       = $againHint
  }
}

if ($Current) {
  $recent = @(Get-ThreadFiles | Sort-Object LastWriteTime -Descending)
  $pick = $null
  if ($Cwd) {
    # Claude Code の履歴のディレクトリ名は、作業ディレクトリのパスの英数字以外を `-` にしたもの
    $key = $Cwd.TrimEnd('\', '/') -replace '[^A-Za-z0-9]', '-'
    $pick = Get-ChildItem -Path (Join-Path $ProjectsDir $key) -Filter *.jsonl -File -ErrorAction SilentlyContinue |
      Sort-Object LastWriteTime -Descending | Select-Object -First 1
    if (-not $pick) { Write-Warning "作業ディレクトリのキー '$key' の履歴が無い。最新の更新を選ぶ（外れうる）" }
  }
  if (-not $pick) { $pick = $recent | Select-Object -First 1 }
  # 選んだ会話の更新の前後 CurrentWindowMin 分以内に、別の会話も更新されていたら、並行している
  $others = @($recent | Where-Object { $_.BaseName -ne $pick.BaseName -and [math]::Abs(($_.LastWriteTime - $pick.LastWriteTime).TotalMinutes) -le $CurrentWindowMin })
  foreach ($o in $others) { Write-Warning "並行の可能性: $($o.BaseName.Substring(0, 8))（$($o.Directory.Name)、更新 $($o.LastWriteTime.ToString('HH:mm:ss'))）" }
  $pick.BaseName
  return
}

if ($Report) {
  $th = @(Import-Csv -Path $Out -Encoding utf8 | Where-Object { $_.last_ts -ge $Since })
  $ss = if (Test-Path $Sessions) { @(Import-Csv -Path $Sessions -Encoding utf8) } else { @() }
  $linked = @($ss | ForEach-Object thread_id)
  $now = [datetime]::UtcNow
  "== スレッド（last_ts が $Since 以降）: $($th.Count) 件、うちセッションに紐づく $(@($th | Where-Object { $_.thread_id -in $linked }).Count) 件"
  $big = @($th | Where-Object { [int]$_.prompts -ge 3 })
  if ($big.Count) {
    $med = Get-Pct (@($big | ForEach-Object { [int]$_.turn_med_s }) | Sort-Object) 0.5
    "プロンプト3回以上のスレッド $($big.Count) 件: ターン長の中央値の中央値 ${med} 秒、out トークン合計 $(($big | Measure-Object out_tokens -Sum).Sum)"
  }
  # 再利用（参照）: 業務側のスレッド（exmem・kit の保守を除く）が、knowledge を読んだか。know_reads が空の行（履歴が消えた古い行）は母数に入れない
  $work = @($th | Where-Object { [int]$_.prompts -ge 3 -and $_.project_key -notmatch 'exmem$|workflow-kit$' -and $_.know_reads -ne '' })
  if ($work.Count) {
    $hit = @($work | Where-Object { [int]$_.know_reads -gt 0 })
    $miss = @($work | Where-Object { [int]$_.know_reads -eq 0 -and [int]$_.know_searches -gt 0 })
    "== 再利用（業務側のスレッド、プロンプト3回以上 $($work.Count) 件。下限値: Read と検索の呼び出しだけ数える）"
    "参照率（knowledge を1件以上 Read）: $($hit.Count)/$($work.Count) = $('{0:P0}' -f ($hit.Count / $work.Count))。参照したスレッドの Read 件数の中央値: $(Get-Pct (@($hit | ForEach-Object { [int]$_.know_reads }) | Sort-Object) 0.5)"
    "空振りの合図（検索したが 1件も読まなかった）: $($miss.Count) 件"
    $kdir = Join-Path $PSScriptRoot '../../resources/exmem/knowledge'
    $all = if (Test-Path $kdir) { @(Get-ChildItem $kdir -Filter *.md -File | ForEach-Object Name) } else { @() }
    $readBy = @{}
    foreach ($r in $work) { foreach ($f in ($r.know_files -split ';' | Where-Object { $_ })) { $readBy[$f] = 1 + [int]$readBy[$f] } }
    if ($all.Count) { "knowledge $($all.Count) 件のうち、期間内に1度でも読まれた: $(@($all | Where-Object { $readBy.ContainsKey($_) }).Count) 件（未参照は縮小・統合の候補。判定ではなく合図）" }
    if ($readBy.Count) { ($readBy.GetEnumerator() | Sort-Object Value -Descending | Select-Object -First 8 | ForEach-Object { "$($_.Key)=$($_.Value)" }) -join '、' | ForEach-Object { "よく読まれる: $_" } }
  }
  # kit の手順書の参照（どのフックが実際に読まれているか）。保守のスレッドも含む
  $kitRead = @{}
  foreach ($r in @($th | Where-Object { $_.kit_files })) { foreach ($f in ($r.kit_files -split ';' | Where-Object { $_ })) { $kitRead[$f] = 1 + [int]$kitRead[$f] } }
  if ($kitRead.Count) {
    $kd = Join-Path $PSScriptRoot '../../resources/workflow-kit'
    $unread = if (Test-Path $kd) { @(Get-ChildItem $kd -Filter *.md -File | ForEach-Object Name | Where-Object { -not $kitRead.ContainsKey($_) }) } else { @() }
    "== kit の手順書を読んだスレッド数: $(($kitRead.GetEnumerator() | Sort-Object Value -Descending | ForEach-Object { "$($_.Key)=$($_.Value)" }) -join '、')"
    if ($unread) { "期間内に読まれていない: $($unread -join '、')" }
  }
  # again（目的「言わない」の直接指標）と、wrap の遠回りの自己申告
  $ag = @(Import-Csv -Path (Join-Path $PSScriptRoot 'events.csv') -Encoding utf8 | Where-Object kind -eq 'again')
  $hint = ($th | Where-Object again_hint -ne '' | ForEach-Object { [int]$_.again_hint } | Measure-Object -Sum).Sum
  "== again: ユーザーが付けた $($ag.Count) 件（うち、情報が既に知識・docs にあった $(@($ag | Where-Object answerable -eq '1').Count) 件 = 探し方の問題）。会話履歴の機械検出（目安・誤検出あり）: $hint プロンプト"
  $dt = @($ss | Where-Object { $_.detour } | Group-Object detour | ForEach-Object { "$($_.Name)=$($_.Count)" })
  "遠回りの自己申告（sessions.csv の detour）: $(if ($dt) { $dt -join '、' } else { '記録なし' })"
  # 常時読み込み（コスト側。開始時に読む指示の字数。増やさない）
  $root = Join-Path $PSScriptRoot '../..'
  # 2026-10-08 のログ分割で decisions.md を、AGENTS の縮小で docs-rules.md を、開始時の読み込みから外した（ベースラインの 79,804 字は、この 2 つの 22,407 字を含む）
  $startFiles = 'AGENTS.md', 'resources/AGENTS.md', 'docs/log.md'
  $sizes = foreach ($p in $startFiles) { $f = Join-Path $root $p; [pscustomobject]@{ p = $p; n = if (Test-Path $f) { [IO.File]::ReadAllText($f).Length } else { 0 } } }
  "== 常時読み込み（開始時に読む指示の字数）: 合計 $(($sizes | Measure-Object n -Sum).Sum) 字（$(($sizes | ForEach-Object { "$($_.p)=$($_.n)" }) -join '、')）"
  "== 無駄の候補（判定ではなく合図。中身を見て判断する）"
  $rows = foreach ($r in $th) {
    $why = @()
    $idle = ($now - [datetime]::Parse($r.last_ts).ToUniversalTime()).TotalDays
    if ($r.thread_id -notin $linked -and [int]$r.prompts -ge 3) { $why += 'セッションに紐づかない' }
    if ($r.thread_id -notin $linked -and $idle -ge $IdleDays) { $why += "放置 $([math]::Floor($idle)) 日" }
    if ([int]$r.tools_total -ge 10 -and [int]$r.tool_errors / [int]$r.tools_total -ge 0.2) { $why += "ツールエラー率 $('{0:P0}' -f ([int]$r.tool_errors / [int]$r.tools_total))" }
    if ([int]$r.capped_turns -ge 1) { $why += "打ち切りターン $($r.capped_turns) 件" }
    if ($why) { [pscustomobject]@{ thread = $r.thread_id.Substring(0, 8); key = $r.project_key; prompts = $r.prompts; out_tokens = $r.out_tokens; 合図 = $why -join '、' } }
  }
  if ($rows) { $rows | Format-Table -AutoSize | Out-String -Width 200 } else { '無し' }
  return
}

$existing = @{}
if (Test-Path $Out) { Import-Csv -Path $Out -Encoding utf8 | ForEach-Object { $existing[$_.thread_id] = $_ } }
$updated = 0
foreach ($f in Get-ThreadFiles) {
  $row = Read-Thread $f
  if ($row) { $existing[$row.thread_id] = $row; $updated++ }
}
$existing.Values | Sort-Object first_ts | Select-Object $Columns | Export-Csv -Path $Out -Encoding utf8 -NoTypeInformation
# 改行コードは LF に統一する（.gitattributes）。Export-Csv は Windows で CRLF を書く
[System.IO.File]::WriteAllText($Out, ([System.IO.File]::ReadAllText($Out) -replace "`r`n", "`n"), [System.Text.UTF8Encoding]::new($false))
"更新 $updated 件、合計 $($existing.Count) 件 → $Out"
