/*********************************************************************************************************
* ContainerJobManager.hpp
* Note: Phoenix Container Service JobObject Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_CONTAINER_JOBMANAGER_HPP
#define PHOENIX_CONTAINER_JOBMANAGER_HPP

#include <Windows.h>

class ContainerJobManager{
private:
    HANDLE hJob;
    bool JobObjectCheck();
public:
    ContainerJobManager();
    ~ContainerJobManager();
    bool Initialize();
    void Destory();
    static HRESULT StartRestrictedProcess(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszWorkdir);
    static HRESULT StartRestrictedProcessEx(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszWorkdir,DWORD &pid);
};


#endif
