/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: ModuleLoader.cpp
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <Runtime/Runtime.h>

typedef int(* PackageInitialize)(int Argc,char **Argv);

int moduleStartup(const char *module,int Argc,char **Argv)
{
    HMODULE hMod=GetModuleHandleA(module);
    PackageInitialize entry=static_cast<PackageInitialize>(GetProcAddress(hMod,"PackageInitialize"));
    if(entry==nullptr)
        return -1;
    int ret=entry(Argc,Argv);
    FreeLibrary(hMod);
    CloseHandle(hMod);
    return ret;
}

DWORD WINAPI ModuleStartupLaucnherThread(LPVOID lpData)
{
    //
    if(lpData==nullptr)
        return 1;
    LauncherParam *lparma=static_cast<LauncherParam*>(lpData);
    if(!ComponentInitializeEx())
        return -1;
    ////
    ComponentUnInitialze();
    return 0;
}
