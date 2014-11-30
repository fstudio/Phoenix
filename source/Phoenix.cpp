/*********************************************************************************************************
* Phoenix.cpp
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note:
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>
#include <map>
#ifndef _WIN32
#error "Only Support Windows"
#endif
#include <Winternl.h>
#include <Processthreadsapi.h>
#include "PhoenixUI.h"

//class PhoenixWindow;
static std::map<int,HINSTANCE> ChildProcessMap;

class ProcessCommandLine{
private:
    int m_Argc;
    wchar_t** m_Argv;
    //Error count
    unsigned erc;
    unsigned dwRet;
public:
    std::map<std:;wstring, std::wstring> pclMap;
    std::vector<std::wstring> filevector;
    ProcessCommandLine(int Argc,const wchar_t* Argv[]):m_Argc(Argc),erc(0),dwRet(0)
    {
        m_Argv=Argv;
        this->ParserAllocate();

    }
    unsigned GetParserStatusCode()
    {
        return this->dwRet;
    }
protected:
    bool ParserAllocate()
    {
        std::pair< std::map<std::wstring,std::wstring>::iterator,bool> bRet;
        if(m_Argc<=1)
        {
            pclMap.insert(std::map<std::wstring, std::wstring>::value_type(L"-Default",L"untitled"));
        }
        int i=1;
        while(i<m_Argc)
        {
            if(m_Argv[i][0]==L'-'&&i+1<m_Argv)
            {
                if(m_Argv[i+1][0]==L'-')
                {
                    pclMap.insert(std::map<std::wstring, std::wstring>::value_type(m_Argv[i],L"Normal"));
                    i++
                    erc++;
                    dwRet+=0x0001;
                }
                //-LoadConfig C:\Config.config
                bRet=pclMap.insert(std::map<std::wstring, std::wstring>::value_type(m_Argv[i],m_Argv[i+1]));
                if(wcscmp_s(m_Argv[i],20,L"-FileAdd")==0)
                {
                     filevector.insert(std::vector<std::wstring>::value_type(m_Argv[i+1]));
                }
                i=i+2;
            }else{
                if(m_Argv[i][0]==L'-')
                {
                    erc++;
                    pclMap.insert(std::map<std::wstring,std::wstring>::value_type(m_Argv[i],L"Normal"));
                    dwRet=0x0010;
                    //return false;
                }else{
                    bRet=pclMap.insert(std::map<std::wstring, std::wstring>::value_type(L"-FileAdd",m_Argv[i]));
                    if(!bRet.second )
                    {
                        filevector.insert(std::vector<std::wstring>::value_type(m_Argv[i]));
                    }
                    erc++;
                    dwRet+=0x1000;
                }
                i++;
            }
        }
        return true;
    }
};


class HandleHelp{
public:
    HANDLE hAndle;
    HandleHelp()
    {
        hAndle=nullptr;
    }
    ~HandleHelp()
    {
        if(hAndle)
        {
            CloseHandle(hAndle);
            hAndle=nullptr;
        }
    }
    bool Delete()
    {
        if(hAndle)
        {
            CloseHandle(hAndle);
            hAndle=nullptr;
        }
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

bool PhoenixRadio(ProcessCommandLine* pCml)
{
    return true;
}



int WINAPI PhoenixUIModel(ProcessCommandLine* pCml)
{
    if(!PhoenixCreateMutex())
    {
         if(PhoenixRadio(pCml))
            return 0;
        return 1;
    }
    PhoenixWindow  windowUI;
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
    HandleHelp hAlp=static_cast<HandleHelp>(lParam);
    HANDLE hProcess=GetCurrentProcess();
    DWORD dwParentPid;
    LONG status;
    PROCESS_BASIC_INFORMATION pbi;
    HMODULE hMod = GetModuleHandle(L"NTDLL.DLL");
    NTQUERYINFORMATIONPROCESS NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)GetProcAddress(hMod, 
        "NtQueryInformationProcess");
    if(NtQueryInformationProcess==NULL)
    {
        CloseHandle(hProcess);
        CloseHandle(hMod);
        return 1;
    }
    status = NtQueryInformationProcess(hProcess,ProcessBasicInformation,(PVOID)&pbi,sizeof(PROCESS_BASIC_INFORMATION),NULL);
    dwParentPid=(DWORD)pbi.Reserved3;
    CloseHandle(hProcess);
    ////Wait..

    //MsgWaitForMultipleObjects()
    //MsgWaitForMultipleObjectsEx()
    //Exit
    return 0;
}
//UI Process start
DWORD WINAPI  SupervisionChildProcess(LPVOID lParam)
{
    return 0;
}

int WINAPI   PhoenixTaskModel(ProcessCommandLine* pCml)
{
    //Check Parent is Phoenix?

    DWORD dWaitPid;
    HandleHelp hAlp;

    ////
    //check Wait Thread
    return 0;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANC hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    ProcessCommandLine cmdline(__argc,__wargv);
    if(cmdline.pclMap.find(L"-Task")!=cmdline.pclMap.end())
        return PhoenixTaskModel(&cmdline);
    return PhoenixUIModel(&cmdline);
}

