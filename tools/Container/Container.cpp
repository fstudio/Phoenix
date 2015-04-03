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

class ConsoleAttachEx{
private:
  bool isOpen;
public:
  ConsoleAttachEx()
  {
    if(AttachConsole(ATTACH_PARENT_PROCESS))
    {
      freopen("CONIN$" , "r+t" , stdin);
      freopen("CONOUT$" , "w+t" , stdout);
      freopen("CONOUT$", "w", stderr);
      isOpen=true;
    }else{
      isOpen=false;
    }
  }
  ~ConsoleAttachEx()
  {
    if(isOpen)
    {
      fclose(stdout);
      fclose(stdin);
      fclose(stderr);
      FreeConsole();
    }
  }
};

const wchar_t helpMessage[]=L"\nPhoenix Container Service\0";


int HelpMessagePrint()
{
    ConsoleAttachEx aex;
    DWORD ws;
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), helpMessage, (DWORD) wcslen(helpMessage), &ws, NULL);
    return 0;
}
int cmdUnknownArgument(const wchar_t *args, void *) {
    ConsoleAttachEx aex;
    std::wcerr << L"\ncmd Unknown Options " << args<< std::endl;
    std::wcout<<helpMessage<<std::endl;
    return 1;
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

