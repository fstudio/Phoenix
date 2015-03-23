//+------------------------------------------------------------------------------------------------------
// ContainerService.c
// Note: Phoenix Container RPC Service
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#include "ContainerService.h"



int ContainerServiceInitialize()
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

/* [async] */
void  Launcher(
    /* [in] */ PRPC_ASYNC_STATE Launcher_AsyncHandle,
    /* [unique][in] */ LPCWSTR pszPath,
    /* [unique][in] */ LPCWSTR pszArgs,
    /* [unique][in] */ LPCWSTR pszWorkdir)
{
     RpcAsyncCompleteCall(Launcher_AsyncHandle, NULL);
}
int ContainerRunner(
    LPCWSTR pszPath,
    LPCWSTR pszArgs,
    LPCWSTR pszWorkdir)
{
	if(pszPath||pszArgs)
	{
		///
	}
	return 0;
}
int Kill(LPCWSTR pszApp)
{
    return 0;
}
void ServiceDestory(void)
{
    RpcMgmtStopServerListening(NULL);
    RpcServerUnregisterIf(NULL, NULL, FALSE);
    exit(0);
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
    return(malloc(len));
}

void __RPC_USER  midl_user_free(void __RPC_FAR *ptr)
{
    free(ptr);
}

