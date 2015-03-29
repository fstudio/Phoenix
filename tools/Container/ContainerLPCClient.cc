//+------------------------------------------------------------------------------------------------------
// ContainerLPCClient.cc
// Note: Phoenix Container
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#include "ContainerService.h"
#include <stdio.h>
#include <stdlib.h>
#include "ContainerLPCClient.hpp"

RPC_WSTR pszStringBinding=nullptr;

ContainerRpcManager::ContainerRpcManager()
{
    RpcStringBindingComposeW(nullptr,
        (RPC_WSTR)L"ncalrpc",
        nullptr,
        (RPC_WSTR)L"Phoenix_Container_RPC_Service",
        nullptr,
        &pszStringBinding);
    RpcBindingFromStringBinding(pszStringBinding,&ContainerServiceRPC_Binding);
    this->RpcInit=true;
}

int ContainerRpcManager::Launcher(LPCWSTR pszApp,
    LPCWSTR pszArgs,
    LPCWSTR pszDir)
{
    RPC_ASYNC_STATE async;
    RpcAsyncInitializeHandle( &async, sizeof(async) );
    async.UserInfo = NULL;
    async.NotificationType = RpcNotificationTypeNone;
    ::Launcher(&async, pszApp,pszArgs,pszDir);
    while ( RpcAsyncGetCallStatus(&async) == RPC_S_ASYNC_CALL_PENDING )
    {
        Sleep(1000);
    }
    RpcAsyncCompleteCall( &async, NULL );
    return 0;
}
int ContainerRpcManager::Runner(LPCWSTR pszApp,
    LPCWSTR pszArgs,
    LPCWSTR pszDir)
{
    int Ret=0;
    RpcTryExcept{
        Ret=::ContainerRunner(pszApp,pszArgs,pszDir);
    }
    RpcExcept(1)
    {
        //
        fprintf(stderr, "ContainerService RPC Failed Stop: %d\n",RpcExceptionCode());
    }
    RpcEndExcept
    return Ret;
}
int ContainerRpcManager::LauncherWithJob(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir)
{
    int Ret=0;
    RpcTryExcept{
        Ret=::LauncherWithJob(pszApp,pszArgs,pszDir);
    }
    RpcExcept(1)
    {
        //
        fprintf(stderr, "ContainerService RPC Failed Stop: %d\n",RpcExceptionCode());
    }
    RpcEndExcept
    return Ret;
}

int ContainerRpcManager::ProcessExit(LPCWSTR pszApp)
{
    int Ret=0;
    RpcTryExcept{
        Ret=::ContainerProcessExit(pszApp);
    }
    RpcExcept(1)
    {
        //
        fprintf(stderr, "ContainerService RPC Failed Stop: %d\n",RpcExceptionCode());
    }
    RpcEndExcept
    return Ret;
}

void ContainerRpcManager::Destory()
{
    RpcTryExcept{
        ServiceDestory();
    }
    RpcExcept(1)
    {
        //
        fprintf(stderr, "ContainerService RPC Failed Stop: %d\n",RpcExceptionCode());
    }
    RpcEndExcept
    RpcStringFree(&pszStringBinding);
    RpcBindingFree(&ContainerServiceRPC_Binding);
}
ContainerRpcManager::~ContainerRpcManager()
{
    RpcStringFree(&pszStringBinding);
    RpcBindingFree(&ContainerServiceRPC_Binding);
}

bool Associated()
{
    return true;
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
     return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr)
{
     free(ptr);
}