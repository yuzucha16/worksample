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
  最も新しく更新された会話の ID だけを出す（終了処理で sessions.csv の thread_id に書く用）。並行セッションがあると外れうる。

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
  [switch]$Current,
  [switch]$Report
)

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
  foreach ($line in [System.IO.File]::ReadLines($file.FullName)) {
    if (-not $line.Contains('"timestamp"')) { continue }
    try { $o = $line | ConvertFrom-Json } catch { continue }
    if ($o.isSidechain -or $o.type -notin 'user', 'assistant') { continue }
    $ts = [datetime]$o.timestamp
    $real = $false
    $tools = 0
    if ($o.type -eq 'user') {
      $real = -not $o.toolUseResult -and -not $o.isMeta
      if ($o.message.content -is [array]) {
        $toolErrors += @($o.message.content | Where-Object { $_.type -eq 'tool_result' -and $_.is_error }).Count
      }
    } else {
      if ($o.message.content -is [array]) { $tools = @($o.message.content | Where-Object type -eq 'tool_use').Count }
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
  }
}

if ($Current) {
  Get-ThreadFiles | Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty BaseName
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
$existing.Values | Sort-Object first_ts | Export-Csv -Path $Out -Encoding utf8 -NoTypeInformation
# 改行コードは LF に統一する（.gitattributes）。Export-Csv は Windows で CRLF を書く
[System.IO.File]::WriteAllText($Out, ([System.IO.File]::ReadAllText($Out) -replace "`r`n", "`n"), [System.Text.UTF8Encoding]::new($false))
"更新 $updated 件、合計 $($existing.Count) 件 → $Out"
