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
#include <Shobjidl.h>
#include <vector>
#include "UIWindow.h"
#include "Header.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include "TaskProcess.hpp"
#include <iostream>
//class UIWindow;
static std::map<int,HINSTANCE> ChildProcessMap;

int cmdUnknownArgument(const wchar_t *args, void *) {
    std::wcout << L"cmd Unknown Options " <<args<<std::endl;
    return 1;
}


int WINAPI UIChannelProviders(bool isNew)
{
    if(!isNew)
    {
        if(!CreateMutexProviders())
        {
            return 1;
        }
    }
	SetCurrentProcessExplicitAppUserModelID(PHOENX_EDITOR_APPID);
    UIWindow  windowUI;
    windowUI.Runable();
    //while()
    return 0;
}

///<summary>
// int WINAPI TaskChannelProviders
///</summary>
int WINAPI TaskChannelProviders()
{
    return 0;
}


int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
    ///
    bool help=false;
    bool bTask=false;
    bool bInit=false;
    bool bReset=false;
    bool newWindow=false;
    bool bVersion=false;
    bool bSetting=false;
    std::wstring  profile;
    std::vector<std::wstring> vfile;
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
    Args.AddArgument(L"-Reset",argT::NO_ARGUMENT,&bReset,
        L"Reset Phoenix Editor Environment");
    Args.AddArgument(L"-Profile",argT::SPACE_ARGUMENT,&profile,
        L"Run Other Profile Environment");
    Args.AddArgument(L"-Setting",argT::NO_ARGUMENT,&bSetting,
        L"Reset Phoenix Editor Environment");
    Args.AddArgument(L"-File",argT::MULTI_ARGUMENT,&vfile,
        L"Open File");
    Args.StoreUnusedArguments(true);
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();

    if(!parsed)
        return 1;
    if(bTask)
    {
        Task::TaskProcess taskProcess;
        return taskProcess.Execute();
    }
    wchar_t** newArgv = 0;
    int newArgc = 0;
    Args.GetUnusedArguments(&newArgc, &newArgv);
    Args.DeleteRemainingArguments(newArgc, &newArgv);
    return 0;
}

