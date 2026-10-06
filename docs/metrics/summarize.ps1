#Requires -Version 7
<#
.SYNOPSIS
  interview-events.csv を、全体・Area・Project・セッションの単位で集計する。指標の定義は README.md。

.PARAMETER Path
  集計する CSV。省略すると、このスクリプトと同じディレクトリの interview-events.csv。

.PARAMETER Basis
  行を `live` か `backfill` に絞る。省略すると全部。

.EXAMPLE
  pwsh -NoProfile -File docs/metrics/summarize.ps1
  pwsh -NoProfile -File docs/metrics/summarize.ps1 -Basis live
#>
[CmdletBinding(PositionalBinding = $false)]
param(
  [string]$Path = (Join-Path $PSScriptRoot 'interview-events.csv'),
  [ValidateSet('', 'live', 'backfill')][string]$Basis = ''
)

$rows = @(Import-Csv -Path $Path -Encoding utf8)
if ($Basis) { $rows = @($rows | Where-Object basis -eq $Basis) }

function Format-Rate($num, $den) { if ($den -eq 0) { '-' } else { '{0:P0}' -f ($num / $den) } }

function Get-Stat($label, $target, $g) {
  $g = @($g)
  $answered = @($g | Where-Object answered -eq '1')
  $adopted = @($g | Where-Object adopted -eq '1')
  $fix = @($g | Where-Object fix -eq '1')
  $supp = @($g | Where-Object supplement -eq '1')
  $misfit = @($answered | Where-Object { $_.fix -eq '1' -or $_.supplement -eq '1' })
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
    修正   = $fix.Count
    補足   = $supp.Count
    適合率 = Format-Rate ($answered.Count - $misfit.Count) $answered.Count
    冗長率 = Format-Rate @($g | Where-Object answerable -eq '1').Count $g.Count
    覆り率 = Format-Rate $rev.Count $known.Count
  }
}

foreach ($kind in 'interview', 'approval') {
  $k = @($rows | Where-Object kind -eq $kind)
  if ($k.Count -eq 0) { continue }
  "== kind: $kind（基準: $(if ($Basis) { $Basis } else { '全行' })）"
  $out = @(Get-Stat '全体' '-' $k)
  $out += $k | Group-Object area | Sort-Object Name | ForEach-Object { Get-Stat 'area' $_.Name $_.Group }
  $out += $k | Group-Object { "$($_.area)/$($_.project)" } | Sort-Object Name | ForEach-Object { Get-Stat 'project' $_.Name $_.Group }
  $out += $k | Group-Object session | Sort-Object Name | ForEach-Object { Get-Stat 'session' $_.Name $_.Group }
  # Format-Table は端末幅で列を落とすので、Markdown の表として出す
  $cols = $out[0].PSObject.Properties.Name
  '| ' + ($cols -join ' | ') + ' |'
  '|' + ('---|' * $cols.Count)
  foreach ($r in $out) { '| ' + (($cols | ForEach-Object { $r.$_ }) -join ' | ') + ' |' }
  ''
}
if ($rows.Count -eq 0) { '該当する行がない' }
