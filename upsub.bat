@echo off
cd /d %~dp0
git submodule init
 git submodule foreach git pull 