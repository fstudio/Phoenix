/*********************************************************************************************************
* TaskProcess.cpp
* Note: Phoenix Task Process
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <winternl.h>
#include <Processthreadsapi.h>
#include <wchar.h>

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



int WINAPI   PhoenixTaskModel()
{
    //Check Parent is Phoenix?

    DWORD dWaitPid;
    ForceHANDLE hAlp;

    ////
    //check Wait Thread
    return 0;
}

