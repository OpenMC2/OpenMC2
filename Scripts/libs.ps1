param([string]$toolset = "v141", [switch]$force = $false)

$expmaj = "2"
$expmin = "0"

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
  
  if (Test-Path $libspath) {
    Remove-Item -Force -Recurse $libspath
  }
  New-Item -Force -ItemType Directory $libspath > $null
  
  # Github has disabled TLS <= 1.1, so make sure that net.webclient uses TLSv1.2
  [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.SecurityProtocolType]::Tls12;
  
  # This is a lot faster than Invoke-WebRequest
  (New-Object System.Net.WebClient).Downloadfile($zipurl, $zippath)
  if (Test-Path $zippath) {
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zippath, $libspath)
    Remove-Item $zipPath -Force
    
    "$toolset;$expmaj.$expmin" > $versionpath
  }
}
