param([string]$toolset = "vs150", [switch]$force = $false)

$expmaj = "1"
$expmin = "1"

$libspath = "$PSScriptRoot\..\libs"
$versionpath = "$libspath\version.txt"

$zipname = "OpenMC2-libs-$toolset.zip"
$zippath = "$libspath\$zipname"
$zipurl = "https://github.com/OpenMC2/Dependencies/releases/download/v$expmaj.$expmin/$zipname"

$installed = "null;0.0"

if (Test-Path $versionpath) {
  $installed = [IO.File]::ReadAllText($versionpath)
}

$majmin = $installed.split(".")

if ($force -or ($majmin[0] -ne "$toolset;$expmaj") -or ($majmin[1] -lt $expmin)) {
  Write-Host "Updating dependencies..."
  
  if (Test-path $libspath) {
    Remove-Item -Force -Recurse $libspath
  }
  New-Item -Force -ItemType Directory $libspath > $null
  
  # This is a lot faster than Invoke-WebRequest
  $wc = New-Object net.webclient
  $wc.Downloadfile($zipurl, $zippath)
  Add-Type -AssemblyName System.IO.Compression.FileSystem
  [System.IO.Compression.ZipFile]::ExtractToDirectory($zippath, $libspath)
  Remove-Item $zipPath -Force
  
  "$toolset;$expmaj.$expmin" > $versionpath
}
