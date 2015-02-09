@echo off
ECHO "Build def File:tiny_impdef.exe PackageRuntime.dll -o PackageRuntime.def"
SET PATH=%~dp0../TinyCC/X86/tcc;%PATH%
cmd /k
