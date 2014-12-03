@echo off
::
IF not exist %~dp0include/rapidjson goto NEXTOPT
rd /s /q "%~dp0include/rapidjson"

:NEXTOPT

goto :EOF
