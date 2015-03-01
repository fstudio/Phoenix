/*********************************************************************************************************
* Phoenix.cpp
* Note: Phoenix Main 
* E-mail:<forcemz@outlook.com>
* Data: @2014.08
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef _WIN32
#error "Only Support Windows"
#endif
#include <Phoenix.h>
#include <Winternl.h>
#include <Processthreadsapi.h>
#include <wchar.h>
#include <string>
#include <map>
#include "PhoenixUI.h"
#include "CommandLineArgumentsEx.hpp"


//class UIWindow;
static std::map<int,HINSTANCE> ChildProcessMap;



class ForceHANDLE{
public:
    HANDLE m_handle;
    ForceHANDLE()
    {
        m_handle=nullptr;
    }
    ForceHANDLE(HANDLE hPtr)
    {
        if(hPtr)
            this->m_handle=hPtr;
    }
    HANDLE Get() const{
        return this->m_handle;
    }
    ~ForceHANDLE()
    {
        if(m_handle)
        {
            CloseHandle(m_handle);
            m_handle=nullptr;
        }
    }
    bool Delete()
    {
        if(m_handle)
        {
            CloseHandle(m_handle);
            m_handle=nullptr;
        }
    }
    ForceHANDLE& operator=(HANDLE hPtr)
    {
        m_handle=static_cast<HANDLE>(hPtr);
        return *this;
    }
    ForceHANDLE& operator=(const ForceHANDLE &forceHandle)
    {
        this->m_handle=static_cast<HANDLE>(forceHandle.Get());
        return *this;
    }
};


bool PhoenixCreateMutex()
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, _T("PhoenixMutex+UIChannel"));
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return false;
    }
    return true;
}

bool PhoenixRadio()
{
    return true;
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

/*
Winternl.h:

NTSTATUS WINAPI NtQueryInformationProcess(
__in HANDLE ProcessHandle,
__in PROCESSINFOCLASS ProcessInformationClass,
__out PVOID ProcessInformation,
__in ULONG ProcessInformationLength,
__out_opt PULONG ReturnLength
);

*/

typedef NTSTATUS (__stdcall * NTQUERYINFORMATIONPROCESS)
(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PPEB PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

//Task Process start
DWORD  WINAPI   WaitForParentExitThread(LPVOID lParam)
{
    ForceHANDLE hAlp=static_cast<ForceHANDLE>(lParam);
    HANDLE hProcess=GetCurrentProcess();
    DWORD dwParentPid;
    LONG status;
    PROCESS_BASIC_INFORMATION pbi;
    HMODULE hMod = GetModuleHandle(L"NTDLL.DLL");
    NTQUERYINFORMATIONPROCESS NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)GetProcAddress(hMod,"NtQueryInformationProcess");
    if(NtQueryInformationProcess==NULL)
    {
        CloseHandle(hProcess);
        ///FreeLibrary(hMod);
        CloseHandle(hMod);
        return 1;
    }
    status = NtQueryInformationProcess(hProcess,ProcessBasicInformation,(PVOID)&pbi,sizeof(PROCESS_BASIC_INFORMATION),NULL);
    dwParentPid=(DWORD)pbi.Reserved3;
    CloseHandle(hProcess);
    ////Wait..
    ///FreeLibrary(hMod);
    //MsgWaitForMultipleObjects()
    //MsgWaitForMultipleObjectsEx()
    //Exit
    //NTDLL always be called . so ....

    return 0;
}
//UI Process start
DWORD WINAPI  SupervisionChildProcess(LPVOID lParam)
{
    if(ChildProcessMap.empty())
    {
        //
    }else{
    //Query
    }
    return 0;
}

int WINAPI   PhoenixTaskModel()
{
    //Check Parent is Phoenix?

    DWORD dWaitPid;
    ForceHANDLE hAlp;

    ////
    //check Wait Thread
    return 0;
}

class Arguments{
private:
    std::vector<wchar_t *> argv_;
public:
    static Arguments Main()
    {
        int ac;
        LPWSTR *w_av = CommandLineToArgvW(GetCommandLineW(), &ac);
        std::vector<std::wstring> av1(ac);
        std::vector<wchar_t const *> av2(ac);
        for (int i = 0; i < ac; i++) {
            av1[i]=w_av[i];
            av2[i] = av1[i].c_str();
        }
        LocalFree(w_av);
        return Arguments(ac,&av2[0]);
    }
    Arguments(int Argc,wchar_t const * const* Argv)
    {
        this->argv_.resize(Argc+1);
        for(int i=0;i<Argc;i++)
        {
            this->argv_[i]=wcsdup(Argv[i]);
        }
        this->argv_[Argc]=0;
    }
    ~Arguments()
    {
        for(size_t i=0;i<this->argv_.size();i++){
            free(argv_[i]);
        }
    }
    int argc()const
    {
        return static_cast<int>(this->argv_.size() - 1);
    }
    wchar_t const* const* argv()const{
        return &this->argv_[0];
    }
};

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
    bool bVersion=false;
    std::wstring  textfile;

    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(Argc,Argv);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
        L"Cmd Print Help");
    Args.AddArgument(L"--version", argT::NO_ARGUMENT, &bVersion,
        L"Print Phoenix version");
    Args.AddArgument(L"-Task", argT::NO_ARGUMENT, &bTask,
        L"Execute Phoenix With Task Process");
    Args.AddArgument(L"-Init",argT::NO_ARGUMENT,&bInit,
        L"Initialize Phoenix Editor Environment");
    Args.AddArgument(L"-File",argT::SPACE_ARGUMENT,&textfile,
        L"Open File");
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();

    if(parsed){
        ///
    }else{
        ///
    }
    return 0;
}

