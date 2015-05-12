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
#include "TaskProcess.hpp"
#include <iostream>
//class UIWindow;
static std::map<int,HINSTANCE> ChildProcessMap;


int WINAPI UIChannelProviders(ArgumentsStructure &processParameters)
{
    if(!processParameters.cmdMode&OptionLevel_New)
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
    ProcessParameters processParameters;
    if(!ArgumentsFlow(processParameters))
    {
        return 1;
    }
    if(processParameters.taskMode=InstanceLevel_Task)
        return TaskChannelProviders();
    return UIChannelProviders(processParameters);
}

