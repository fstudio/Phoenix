/*********************************************************************************************************
* Container.cpp
* Note: Phoenix Container
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Precompiled.h"
#include "ContainerAPI.h"
#include "ContainerServiceHub.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include <iostream>

const wchar_t helpMessage[]=L"\nPhoenix Container Service\0";

int cmdUnknownArgument(const wchar_t *args, void *ClientData) {
    ConsoleAttachEx aex;
    std::wcerr << L"\ncmd Unknown Options " << args<< std::endl;
    bool *p=static_cast<bool*>(ClientData);
    *p=true;
    return 1;
}


int HelpMessagePrint()
{
    ConsoleAttachEx aex;
    DWORD ws;
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), helpMessage, (DWORD) wcslen(helpMessage), &ws, NULL);
    return 0;
}

int PrintVersion()
{
    ConsoleAttachEx aex;
    std::cout<<"\n1.0.0.1\n"<<std::endl;
    return 0;
}

int Foreground()
{

    return 0;
}

#undef _CRT_SECURE_NO_WARNINGS


int ContainerServiceInit()
{
    int ret=0;
    if((ret=LauncherContainerStatChecker())!=0)
        return ret;
    ContainerService containerService;
    if(!containerService.Execute())
        ret=1;
    containerService.Destory();
    return 0;
}


int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
    bool help=false;
    bool bForeground=false;
    bool bVersion=false;
    bool isParseFailed=false;
    std::wstring  profile;

    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(Argc,Argv);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
        L"Print Phoenix Container help and exit");
    Args.AddArgument(L"--version", argT::NO_ARGUMENT, &bVersion,
        L"Print Phoenix Container version and exit");
    Args.AddArgument(L"-Foreground", argT::NO_ARGUMENT, &bForeground,
        L"Run Phoenix Container Foreground (debug)");
    Args.AddArgument(L"-Profile",argT::SPACE_ARGUMENT,&profile,
        L"Set Default Profile");
    Args.SetClientData(&isParseFailed);
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();
    if(parsed){
        if(help)
            return HelpMessagePrint();
        if(bVersion)
            return PrintVersion();
        if(isParseFailed)
        {
            MessageBoxW(nullptr,L"Please Check your options!",L"Unknown Command",MB_OK);
            return 1;
        }
    }else{
        ///
        return 1;
    }
    return ContainerServiceInit();
}

