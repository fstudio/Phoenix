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
#include <vector>
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
    bool bReset=false;
    bool newWindow=false;
    bool bVersion=false;
    bool bSetting=false;
    std::wstring  profile;
    std::vector<std::wstring> vfile;
    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    /// AddCallback
    /// GetUnusedArguments
    /// GetRemainingArguments
    /// DeleteRemainingArguments
    ///  arg.AddBooleanArgument("--set-bool-arg1", &bool_arg1, "Test AddBooleanArgument 1");
    /*
    static void* random_ptr = reinterpret_cast<void*>(0x123);
    static int argument(const char* arg, const char* value, void* call_data)
    {
    kwsys_ios::cout << "Got argument: \"" << arg << "\" value: \"" << (value?value:"(null)") << "\"" << kwsys_ios::endl;
    if ( call_data != random_ptr )
    {
    kwsys_ios::cerr << "Problem processing call_data" << kwsys_ios::endl;
    return 0;
    }
   return 1;
   }

   static int unknown_argument(const char* argument, void* call_data)
   {
    kwsys_ios::cout << "Got unknown argument: \"" << argument << "\"" << kwsys_ios::endl;
    if ( call_data != random_ptr )
    {
    kwsys_ios::cerr << "Problem processing call_data" << kwsys_ios::endl;
    return 0;
    }
    return 1;
    }
    ------------------------------------------------------------------------------------------------------------------------------------------------------------
      arg.AddCallback("-A", argT::NO_ARGUMENT, argument, random_ptr, "Some option -A. This option has a multiline comment. It should demonstrate how the code splits lines.");
      arg.AddCallback("-B", argT::SPACE_ARGUMENT, argument, random_ptr, "Option -B takes argument with space");
      arg.AddCallback("-C", argT::EQUAL_ARGUMENT, argument, random_ptr, "Option -C takes argument after =");
      arg.AddCallback("-D", argT::CONCAT_ARGUMENT, argument, random_ptr, "This option takes concatinated argument");
      arg.AddCallback("--long1", argT::NO_ARGUMENT, argument, random_ptr, "-A");
      arg.AddCallback("--long2", argT::SPACE_ARGUMENT, argument, random_ptr, "-B");
      arg.AddCallback("--long3", argT::EQUAL_ARGUMENT, argument, random_ptr, "Same as -C but a bit different");
      arg.AddCallback("--long4", argT::CONCAT_ARGUMENT, argument, random_ptr, "-C");
    */

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
        TaskProcess taskProcess;
        return taskProcess.Execute();
    }
    wchar_t** newArgv = 0;
    int newArgc = 0;
    Args.GetUnusedArguments(&newArgc, &newArgv);
    Args.DeleteRemainingArguments(newArgc, &newArgv);
    return 0;
}

