/*********************************************************************************************************
* Container.cpp
* Note: Phoenix Container
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include "ContainerServiceHub.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include <iostream>

int cmdUnknownArgument(const wchar_t *args, void *) {
std::wcout << L"cmd Unknown Options " << args
              << std::endl;
  return 1;
}


int Foreground()
{
    return 0;
}

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
    bool bTask=false;
    bool bInit=false;
    bool newWindow=false;
    bool bVersion=false;
    std::wstring  profile;

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
    Args.AddArgument(L"-Profile",argT::SPACE_ARGUMENT,&profile,
        L"Set Default Profile");
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();
    ///
    return ContainerServiceInit();
}

