@echo off
REM This foreach sub directory, update svn

SET PATH=D:\SVN\bin;%PATH%

SET WORK_DIR=%~dp0

for /f "delims=" %%a in ('dir /ad /b "%WORK_DIR%"') do (
if exist "%WORK_DIR%\%%a\.svn"  svn up %%a
)
