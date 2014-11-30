#====================================================================
# Configure.ps1
#====================================================================

Function Print-Usage
{
Write-Host "UniversalChardet Configure Script."
}


IF( $argc.Count -eq 1)
{
  Print-Usage
  Exit
}
