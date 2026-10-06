#Requires -Version 7
<#
.SYNOPSIS
  events.csv を、全体・Area・Project・セッション・出どころの単位で集計する。指標の定義は README.md。

.PARAMETER Path
  集計する CSV。省略すると、このスクリプトと同じディレクトリの events.csv。

.PARAMETER Basis
  行を `live` `backfill` `import` のどれかに絞る。省略すると全部。

.PARAMETER Kind
  行を `interview` `approval` `improvement` `gap` のどれかに絞る。省略すると、存在する kind をすべて出す。

.EXAMPLE
  pwsh -NoProfile -File docs/metrics/summarize.ps1
  pwsh -NoProfile -File docs/metrics/summarize.ps1 -Basis live -Kind interview
#>
[CmdletBinding(PositionalBinding = $false)]
param(
  [string]$Path = (Join-Path $PSScriptRoot 'events.csv'),
  [ValidateSet('', 'live', 'backfill', 'import')][string]$Basis = '',
  [ValidateSet('', 'interview', 'approval', 'improvement', 'gap')][string]$Kind = ''
)

$rows = @(Import-Csv -Path $Path -Encoding utf8)
if ($Basis) { $rows = @($rows | Where-Object basis -eq $Basis) }
if ($Kind) { $rows = @($rows | Where-Object kind -eq $Kind) }

function Format-Rate($num, $den) { if ($den -eq 0) { '-' } else { '{0:P0}' -f ($num / $den) } }

# fix が空の行は「未判定」。適合率の母数に入れない（import した行など）
function Get-Stat($label, $target, $g) {
  $g = @($g)
  $answered = @($g | Where-Object answered -eq '1')
  $adopted = @($g | Where-Object adopted -eq '1')
  $judged = @($answered | Where-Object { $_.fix -ne '' })
  $misfit = @($judged | Where-Object { $_.fix -eq '1' -or $_.supplement -eq '1' })
  $known = @($g | Where-Object { $_.reversed -ne '' })
  $rev = @($known | Where-Object reversed -eq '1')
  [pscustomobject]@{
    単位   = $label
    対象   = $target
    質問数 = $g.Count
    回答数 = $answered.Count
    回答率 = Format-Rate $answered.Count $g.Count
    採用数 = $adopted.Count
    採用率 = Format-Rate $adopted.Count $answered.Count
    修正   = @($g | Where-Object fix -eq '1').Count
    補足   = @($g | Where-Object supplement -eq '1').Count
    適合率 = Format-Rate ($judged.Count - $misfit.Count) $judged.Count
    冗長率 = Format-Rate @($g | Where-Object answerable -eq '1').Count @($g | Where-Object answerable -ne '').Count
    覆り率 = Format-Rate $rev.Count $known.Count
    起因ai = @($g | Where-Object cause -eq 'ai').Count
    起因user = @($g | Where-Object cause -eq 'user').Count
    起因review = @($g | Where-Object cause -eq 'review').Count
  }
}

# ループ変数を $Kind にすると、検証つきの引数 $Kind（大文字小文字を区別しない）と衝突する
foreach ($kindName in @($rows | ForEach-Object kind | Select-Object -Unique)) {
  $k = @($rows | Where-Object kind -eq $kindName)
  "== kind: $kindName（基準: $(if ($Basis) { $Basis } else { '全行' })）"
  $out = @(Get-Stat '全体' '-' $k)
  $out += $k | Group-Object area | Sort-Object Name | ForEach-Object { Get-Stat 'area' $_.Name $_.Group }
  $out += $k | Group-Object { "$($_.area)/$($_.project)" } | Sort-Object Name | ForEach-Object { Get-Stat 'project' $_.Name $_.Group }
  $out += $k | Group-Object source | Sort-Object Name | ForEach-Object { Get-Stat 'source' $_.Name $_.Group }
  # セッションは数が多くなりうるので、新しい方から最大10件
  $out += $k | Group-Object session | Sort-Object Name -Descending | Select-Object -First 10 | ForEach-Object { Get-Stat 'session' $_.Name $_.Group }
  # Format-Table は端末幅で列を落とすので、Markdown の表として出す
  $cols = $out[0].PSObject.Properties.Name
  '| ' + ($cols -join ' | ') + ' |'
  '|' + ('---|' * $cols.Count)
  foreach ($r in $out) { '| ' + (($cols | ForEach-Object { $r.$_ }) -join ' | ') + ' |' }
  ''
}
if ($rows.Count -eq 0) { '該当する行がない' }
