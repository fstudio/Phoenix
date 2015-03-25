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
    bool RpcInit;
public:
    ContainerRpcManager();
    ~ContainerRpcManager();
    int Launcher(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir);
    int Runner(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszDir);
    int ProcessKill(LPCWSTR pszApp);
    void Destory();
    bool getStatus(){return this->RpcInit;}
};


#endif
