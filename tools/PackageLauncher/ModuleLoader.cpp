/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: ModuleLoader.cpp
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <Runtime/Runtime.h>
#include <sstream>

typedef int(* PackageInitialize)(int Argc,char **Argv);

int moduleStartup(const char *module,int Argc,char **Argv)
{
    HMODULE hMod=GetModuleHandleA(module);
    PackageInitialize entry=static_cast<PackageInitialize>(GetProcAddress(hMod,"PackageInitialize"));
    if(entry==nullptr)
        return -1;
    /*
    std::vector<const char* > Args;
    std::string moduleName="PackageExample";
    Args.push_back(moduleName.c_str());
    auto Argc=Args.size()-1;
    */
    int ret=entry(Argc,Argv);
    FreeLibrary(hMod);
    CloseHandle(hMod);
    return ret;
}

HRESULT WINAPI PackageLauncher(const char * pk,const char *search,const char * config)
{
    if(!pk||!search)
        return S_FALSE;
    std::stringstream s;
    s<<search<<"/"<<pk<<".dll";
    if(access(s.str().c_str(),4)!=0)
        return false;
    std::string path=s.str();
    s.clear();
    if(config){
        //Laod config
    }
    return S_OK;
}


DWORD WINAPI ModuleStartupLaucnherThread(LPVOID lpData)
{
    //
    if(!lpData)
        return 1;
    LauncherParam *lparma=static_cast<LauncherParam*>(lpData);
    if(!ComponentInitializeEx())
        return -1;
    ////
    ComponentUnInitialze();
    return 0;
}
