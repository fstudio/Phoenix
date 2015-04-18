/*********************************************************************************************************
* Container.cpp
* Note: Phoenix Container EntryPoint
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Precompiled.h"
#include "ContainerAPI.h"
#include "ContainerServiceHub.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include <sstream>
#include "Container.h"


const wchar_t helpMessage[]=L"\nPhoenix Container Service\n\
--help\t\tPrint Phoenix Container help and exit\n\
--version\t\tPrint Phoenix Container version and exit\n\
-Foreground\tRun Phoenix Container Foreground (debug)\n\
-Profile\t\tSet Default Profile\0";

static bool bParsedFailed=false;

int HelpMessagePrint()
{
    MessageBoxW(nullptr,helpMessage,L"Container Help Message",MB_OK|MB_ICONINFORMATION);
    return 0;
}
int cmdUnknownArgument(const wchar_t *args, void *) {
    int nB=0;
    auto ret=TaskDialog(nullptr,GetModuleHandle(nullptr),
        L"Container Failed Message",
        L"cmd Unknown Options:",
        args,
        TDCBF_OK_BUTTON,
        TD_ERROR_ICON,
        &nB);
    bParsedFailed=true;
    return 1;
}



int PrintVersion()
{
    int nB=0;
    std::wstringstream wstr;
    wstr<<L"1.0.1-Alpha";
    auto ret=TaskDialog(nullptr,GetModuleHandle(nullptr),
        L"Phoenix Container",
        L"Container Information:",
        wstr.str().c_str(),
        TDCBF_OK_BUTTON,
        TD_INFORMATION_ICON,
        &nB);
    return 0;
}

int Foreground()
{

    return 0;
}

#undef _CRT_SECURE_NO_WARNINGS


int ContainerServiceInit(Parameters &param,std::wstring &cmdArgs)
{
    int ret=0;
    if((ret=LauncherContainerStatChecker(cmdArgs))!=0)
        return ret;
    ContainerService containerService(param);
    if(!containerService.Execute())
        ret=1;
    containerService.Destory();
    return 0;
}


int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
    std::wstring cmdArgs;
    for(int i=1;i<Argc;i++)
    {
        cmdArgs.assign(L" ");
        cmdArgs.assign(Argv[i]);
    }
    bool help=false;
    bool bVersion=false;
    Parameters param;

    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(Argc,Argv);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
        L"Print Phoenix Container help and exit");
    Args.AddArgument(L"--version", argT::NO_ARGUMENT, &bVersion,
        L"Print Phoenix Container version and exit");
    Args.AddArgument(L"-Foreground", argT::NO_ARGUMENT, &(param.focegournd),
        L"Run Phoenix Container Foreground (debug)");
    Args.AddArgument(L"-Profile",argT::SPACE_ARGUMENT,&(param.profile),
        L"Set Default Profile");
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();
    if(bParsedFailed)
        return 1;
    if(parsed){
        if(help)
            return HelpMessagePrint();
        if(bVersion)
            return PrintVersion();
    }else{
        ///
        return 1;
    }
    return ContainerServiceInit(param,cmdArgs);
}

