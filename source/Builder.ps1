<#
#
#
#
#>
#Builder
$ALLFLAGS="-c -DUNICODE -D_UNICODE"
$CFLAGS="/Tc ${ALLFLAGS}"
$CXXFLAGS="/Tp ${ALLFLAGS}"
$CC="cl"
$CXX="cl"
$LD="link"
$LIB="lib"
IF($BUILD -eq 64)
{
$ASM="ml64"
}ELSE{
$ASM ="ml"
}
$BUILDDIR= [System.IO.Path]::GetDirectoryName($MyInvocation.MyCommand.Definition)
Set-Location $BUILDDIR
$FindRibbonXml=Test-Path "${PWD}\PhoenixRibbon.xml"

IF($FindRibbonXml -ne $True)
{
  Write-Host "Error Not Find PhoenixRibbon.xml" -ForegroundColor Red
  Exit
}
#IEX "uicc PhoenixRibbon.xml PhoenixRibbon.bml /header:PhoenixRibbon.h /res:PhoenixRibbon.rc"
$MANIFEST = "Phoenix.manifest"
#IEX "mt -outputresource:Phoenix.exe"
