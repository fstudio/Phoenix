/*********************************************************************************************************
* ContainerServiceHub.cpp
* Note: Phoenix Container Service Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include <string>
#include <vector>
#include "ContainerAPI.h"
#include "AppContainer.hpp"
#include "ContainerServiceHub.hpp"

BOOL KillProcess(DWORD ProcessId)
{
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return FALSE;
    if(!TerminateProcess(hProcess,0))
        return FALSE;
    return TRUE;
}


bool RemoveContainerInstance(unsigned dwFlags)
{
  switch(dwFlags)
  {
    case 0:
    break;
    default:
    break;
  }
  return true;
}

int ContainerInstance(std::wstring relFile, std::wstring cmdArgs) {
  if (PathFileExistsW(relFile.c_str()) != TRUE)
    return -1;
  return 0;
}

class Container {
private:
  unsigned Id;
  ///std::vector<int> idvector;
public:
  Container() {}
  bool Initialize() {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool bRet=AppContainer::AppContainerInitialize();
    return bRet;
  }
  bool Stop() {
    CoUninitialize();
    bool bRet=AppContainer::AppContainerDelete(RemoveContainerInstance);
    return true;
  }
};


DWORD ContainerRPCService(LPVOID)
{
    if(ContainerRemoteProcedureCall())
        return 1;
    return 0;
}



ContainerService::ContainerService()
{
    ///
}
bool ContainerService::Execute()
{
    Container container;
    bool bRet=true;
    if(!container.Initialize())
        return false;
    DWORD tId;
    HANDLE hThread=CreateThread(NULL, 0, ContainerRPCService, nullptr, 0, &tId);
    if(!hThread)
    {
        container.Stop();
        return false;
    }
    bRet=Manager(tId);
    container.Stop();
    return bRet;
}

bool ContainerService::Manager(unsigned id){
    while(true)
    {
        Sleep(200);
    }
    return true;
}

void ContainerService::Destory()
{
        //
    for(auto i:taskMap)
    {
        KillProcess(i.first);
    }
}
