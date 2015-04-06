/*********************************************************************************************************
* TaskProcess.cpp
* Note: Phoenix Task Process
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <winternl.h>
#include <Processthreadsapi.h>
#include <wchar.h>
#include "Header.hpp"
#include "Arguments.hpp"
#include "CommandLineArgumentsEx.hpp"
#include "TaskProcess.hpp"

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

using namespace Task;

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
DWORD  WINAPI  FollowParentQuit(LPVOID lParam)
{
    ForceHANDLE hAlp=static_cast<ForceHANDLE>(lParam);
    HANDLE hProcess=GetCurrentProcess();
    DWORD dwParentPid;
    LONG status;
    PROCESS_BASIC_INFORMATION pbi;
    HMODULE hMod = GetModuleHandleW(L"NTDLL.DLL");
    NTQUERYINFORMATIONPROCESS NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)GetProcAddress(hMod,"NtQueryInformationProcess");
    if(NtQueryInformationProcess==NULL)
    {
        CloseHandle(hProcess);
        return 1;
    }
    status = NtQueryInformationProcess(hProcess,ProcessBasicInformation,(PVOID)&pbi,sizeof(PROCESS_BASIC_INFORMATION),NULL);
    dwParentPid=(DWORD)pbi.Reserved3;
    ForceHANDLE hFParent=OpenProcess(SYNCHRONIZE,FALSE,dwParentPid);
    if(hFParent.Get()==nullptr)
    {
        //OpenProcess Failed
        return 2;
    }
    DWORD dwRet;
    if((dwRet=WaitForSingleObject(hFParent.Get(),INFINITE))==WAIT_TIMEOUT)
    {
        ///
    }
    if(dwRet==WAIT_FAILED)
    {
        return 2;
    }
    //NTDLL always be called . so ....
    CloseHandle(hProcess);
    return 0;
}


TaskProcess::TaskProcess(int Argv,wchar_t *Argv)
{

}

TaskProcess::TaskProcess(std::vector<std::wstring> &Args)
{

}

TaskProcess::TaskProcess()
{

}

int TaskProcess::Execute()
{
    DWORD dwThread;
    HANDLE hThread=CreateThread(NULL, 0, FollowParentQuit, nullptr, 0, &dwThread);
    if(!hThread)
        return 2;
    CloseHandle(hThread);
    return 0;
}
