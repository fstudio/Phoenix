@echo off
::PackageRuntime.dll export .

tiny_impdef.exe PackageRuntime.dll -o PackageRuntime.def
::cp PackageRuntime.def -->lib path.
::tcc hello.c -lPackageRuntime -o hello.exe
 