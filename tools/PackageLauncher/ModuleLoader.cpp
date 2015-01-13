/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: ModuleLoader.cpp
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>

typedef int(* PackageInitialize)(int Argc,char **Argv);

int StartupModule(const char *module,int Argc,char **Argv)
{
    HMODULE hMod=GetModuleHandleA(module);
    PackageInitialize entry=static_cast<PackageInitialize>(GetProcAddress("PackageInitialize"));
    if(entry==nullptr)
        return -1;
    int ret=entry(Argc,Argv);
    CloseHandle(hMod);
    return ret;
}
