//+------------------------------------------------------------------------------------------------------
// ContainerService.c
// Note: Phoenix Container RPC Service
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#include "ContainerService.h"
#include <TlHelp32.h>
#include <Processthreadsapi.h>
#include <string>
#include "ContainerAPI.h"
#include "AppContainer.hpp"


int ContainerRemoteProcedureCall()
{
        RpcServerUseProtseqEpW(
         (RPC_WSTR)L"ncalrpc",
         RPC_C_PROTSEQ_MAX_REQS_DEFAULT,
         (RPC_WSTR)L"Phoenix_Container_RPC_Service",
         NULL);
    //RpcServerRegisterIf(HelloWorld_v1_0_s_ifspec, NULL, NULL);
    RpcServerRegisterIfEx(
         ContainerServiceRPC_v1_0_s_ifspec, // Interface to register.
         NULL,
         NULL, // Use the MIDL generated entry-point vector.
         RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,
         0,
         NULL);
    RpcServerListen(1,RPC_C_LISTEN_MAX_CALLS_DEFAULT ,FALSE);
    return 0;
}


unsigned RegisterClient(unsigned id)
{
    ///Check PID
    InterlockedExchangeAddEx(true);
    return 0;
}
unsigned UnRegisterClient(unsigned id)
{
    ///
    InterlockedExchangeAddEx(false);
    return 0;
}

/* [async] */
void  Launcher(
    /* [in] */ PRPC_ASYNC_STATE Launcher_AsyncHandle,
    /* [unique][in] */ LPCWSTR pszPath,
    /* [unique][in] */ LPCWSTR pszArgs,
    /* [unique][in] */ LPCWSTR pszWorkdir)
{
    unsigned taskId=LauncherWithAppContainer(pszPath,pszArgs,pszWorkdir);
    if(taskId!=0){
        std::wstring strApp=pszPath;
        ContainerProcessMapAtomAdd(taskId,strApp);
    }
     RpcAsyncCompleteCall(Launcher_AsyncHandle, NULL);
}

int ContainerRunner(
    LPCWSTR pszPath,
    LPCWSTR pszArgs,
    LPCWSTR pszWorkdir)
{
    MessageBoxW(nullptr,pszPath,L"Open App is.",MB_OK);
    unsigned taskId=LauncherWithAppContainer(pszPath,pszArgs,pszWorkdir);
    if(taskId!=0){
        std::wstring strApp=pszPath;
        ContainerProcessMapAtomAdd(taskId,strApp);
    }
    return (int)taskId;
}

int LauncherWithJob(
    LPCWSTR pszPath,
    LPCWSTR pszArgs,
    LPCWSTR pszWorkdir)
{
    //
    return 0;
}


int ContainerProcessExit(LPCWSTR pszApp)
{
    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return -1;
     }
     BOOL bMore = ::Process32First(hProcessSnap, &pe32);
     while(bMore)
     {
        if(_wcsicmp(pe32.szExeFile,pszApp)==0)
         {
            ///TerminateProcess()
            if(FindProcessFromContainer(pe32.th32ProcessID))
            {
                HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,TRUE,pe32.th32ProcessID);
                TerminateProcess(hProcess,1);
                RemoveContainerProcessId(pe32.th32ProcessID);
            }
            ///Query Process Id Find From Map;
             ::CloseHandle(hProcessSnap);
             return 0;
          }
          bMore = ::Process32Next(hProcessSnap, &pe32);
      }
     ::CloseHandle(hProcessSnap);
     return -1;
}

void ServiceDestory(void)
{
    if(LookAccessClientSize()==0){
        RpcMgmtStopServerListening(NULL);
        RpcServerUnregisterIf(NULL, NULL, FALSE);
        ContainerStopKeepAlive();
    }
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER  midl_user_free(void __RPC_FAR *ptr)
{
    free(ptr);
}


