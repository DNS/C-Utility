
$cmd = ""

foreach ($arg in $args) {
	$cmd = "$cmd $arg"
}

#Measure-Command {$cmd}
$cmd = "Measure-Command {$cmd}"

Write-Host $cmd
Invoke-Expression $cmd




