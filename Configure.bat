@echo off
IF not exist %~dp0/include/rapidjson goto CopyRapidJson
rd /s /q "%~dp0include/rapidjson"
:CopyRapidJson
echo "Copy Rapidjson to include folder."
mkdir "%~dp0include/rapidjson"
xcopy "%~dp0deps/rapidjson/include/rapidjson" "%~dp0include/rapidjson" /s /e 
goto :EOF
