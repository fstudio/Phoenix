/*********************************************************************************************************
*   Phoneix Plugin Runtime
*   Note: PackagrRuntime.c This File is Runtime Init.
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
///CoInitialize(NULL);

#include <Windows.h>
#include <Objbase.h>

PKGEXTERN bool ComponentInitialize()
{
    return (CoInitialize(NULL)==S_OK);
}
PKGEXTERN bool ComponentUnInitialze()
{
    CoUninitialize();
    return (GetLastError()==0);
}

PKGEXTERN bool ComponentInitializeEx()
{
    return (CoInitializeEx(NULL,COINIT_MULTITHREADED)==S_OK);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}