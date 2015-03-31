//+------------------------------------------------------------------------------------------------------
// ContainerLPCClient.hpp
// Note: Phoenix Container
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#ifndef CONTAINER_LPC_CLIENT_API_HPP
#define CONTAINER_LPC_CLIENT_API_HPP
#include <Windows.h>
#include <functional>


class ContainerRpcManager{
private:
    bool rpcStatus;
    bool destory;
public:
    ContainerRpcManager();
    ~ContainerRpcManager();
    void ActiveSemaphore();
    int Launcher(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir);
    int LauncherWithJob(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir);
    int Runner(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir);
    int ProcessExit(LPCWSTR pszApp);
    void Destory();
    bool IsInitialize(){return this->rpcStatus;}
};



#endif
