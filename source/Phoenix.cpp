/*********************************************************************************************************
* Phoenix.cpp
* Note: Phoenix Main
* Date: @2014.08
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef _WIN32
#error "Only Support Windows"
#endif
#include <Phoenix.h>
#include <Processthreadsapi.h>
#include <wchar.h>
#include <string>
#include <map>
#include "PhoenixUI.h"
#include "Header.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include "TaskProcess.hpp"

//class UIWindow;
static std::map<int,HINSTANCE> ChildProcessMap;

int cmdUnknownArgument(const wchar_t *args, void *) {
    std::wcout << L"cmd Unknown Options " <<args<<std::endl;
    return 1;
}


int WINAPI PhoenixUIModel()
{
    if(!PhoenixCreateMutex())
    {
         if(PhoenixRadio())
            return 0;
        return 1;
    }
    UIWindow  windowUI;
    windowUI->Runable();
    //while()
    return 0;
}



int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANC hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
    ///
    bool help=false;
    bool bTask=false;
    bool bInit=false;
    bool newWindow=false;
    bool bVersion=false;
    std::wstring  textfile;

    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(Argc,Argv);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
        L"Cmd Print Help");
    Args.AddArgument(L"--version", argT::NO_ARGUMENT, &bVersion,
        L"Print Phoenix version");
    Args.AddArgument(L"-New",argT::NO_ARGUMENT,&newWindow,
        L"Open New Window");
    Args.AddArgument(L"-Task", argT::NO_ARGUMENT, &bTask,
        L"Execute Phoenix With Task Process");
    Args.AddArgument(L"-Init",argT::NO_ARGUMENT,&bInit,
        L"Initialize Phoenix Editor Environment");
    Args.AddArgument(L"-File",argT::SPACE_ARGUMENT,&textfile,
        L"Open File");
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();

    if(parsed){
        if(bTask)
        {
            TaskProcess taskProcess;
            return taskProcess.Execute();
        }
    }else{
        ///
    }
    return 0;
}

