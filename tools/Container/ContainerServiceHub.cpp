/*********************************************************************************************************
* ContainerServiceHub.cpp
* Note: Phoenix Container Service Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include <map>

BOOL KillProcess(DWORD ProcessId)
{
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return FALSE;
    if(!TerminateProcess(hProcess,0))
        return FALSE;
    return TRUE;
}


class ContainerService{
private:
    std::map<unsigned, unsigned> taskMap;
    bool BindPorts()
    {
        return true;
    }
public:
    ContainerService()
    {
        //
    }
    static bool ContainerServiceStart()
    {
        return 0;
    }
    void ContainerServiceDestory()
    {
        //
        for(auto i:taskMap)
        {
            KillProcess(i.first);
        }
    }
};

DWORD ContainerServiceManagerThread(LPVOID lParam)
{
    if(lParam==nullptr)
        return 1;
    ContainerService *sevice=reinterpret_cast<ContainerService *>(lParam);
    return 0;
}



