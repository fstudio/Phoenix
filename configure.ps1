<##########################################################################################
* configure.ps1
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoeinx Configure PowerShell Script
* E-mail:<forcemz@outlook.com>
* @2014.08
###########################################################################################>
$PBVMAX=1
$PBVMIN=0
$PBVPATCH=0
$PBVBUILD=1
$PBRevision=115
$PhoenixBuildSystemVersion = "${PBVMAX}.${PBVMIN}.${PBVPATCH}.${PBVBUILD}"
$Host.UI.RawUI.WindowTitle ="Phoenix Configure TaskScheduler |PowerShell"

Function Get-Usage
{
    Write-Host "OVERVIEW: Phoeinx Configure Script Assistant"
    Write-Host "USAGE: configure.ps1 [options] <input> `n"
    Write-Host "OPTIONS:"
    Write-Host "`t--build=release|debug"
    Write-Host "`t--prefix=folder"
}

Function Print-Version
{
   Write-Host "Phoeinx Configure Script Assistant"
   Write-Host "Phoenix Build System version: ${PhoenixBuildSystemVersion}  (${PBRevision}.Revision)"
   Write-Host "Copyright © 2015 The Force Studio .All Rights Reserved."
}

<#

Import-Module BitsTransfer
$url = 'url'
Start-BitsTransfer $url "zz""
Invoke-Item "zz"

#>

#Write-Host "Start Configure Phoenix Pro Text Editor Build Environment"
