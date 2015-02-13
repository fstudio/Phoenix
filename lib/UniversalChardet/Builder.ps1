<#
*  Phoenix Universal Chardet Build
#>

$CXX="cl"
$CXXFLAGS="-O2"
#$argv[1] -eq shared
IEX "${CXX} ${CXXFLAGS} base/CharDistrbution.cpp"