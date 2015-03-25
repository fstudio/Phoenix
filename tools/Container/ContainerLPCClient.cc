//+------------------------------------------------------------------------------------------------------
// ContainerLPCClient.cc
// Note: Phoenix Container
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#include "ContainerService.h"




int WINAPI LauncherWithLPC(LPCWSTR pszApp,
    LPCWSTR pszArgs,
    LPCWSTR pszDir)
{
    return 0;
}


void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
     return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr)
{
     free(ptr);
}
