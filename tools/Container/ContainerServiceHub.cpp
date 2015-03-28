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
#include <atomic>
#include "ContainerAPI.h"
#include "AppContainer.hpp"
#include "ContainerServiceHub.hpp"

/////CriticalSection taskMap
std::unordered_map<unsigned,std::wstring> taskMap;
CRITICAL_SECTION g_cs;


bool FindProcessFromContainer(unsigned pid)
{
    EnterCriticalSection(&g_cs);
    auto iter=taskMap.find(pid);
    bool bRet=true;
    if(iter==taskMap.end())
    {
        bRet= false;
    }
    LeaveCriticalSection(&g_cs);
    return bRet;
}

bool ContainerProcessMapAtomAdd(unsigned pid,std::wstring appName)
{
    EnterCriticalSection(&g_cs);
    auto ret=taskMap.insert(std::pair<unsigned,std::wstring>(pid,appName));
    LeaveCriticalSection(&g_cs);
    return ret.second;
}
bool RemoveContainerProcessId(unsigned pid)
{
    EnterCriticalSection(&g_cs);
    auto iter=taskMap.find(pid);
    bool bRet=true;
    if(iter==taskMap.end()){
        bRet=false;
        goto LeaveCs;
    }
    taskMap.erase(pid);
LeaveCs:
    LeaveCriticalSection(&g_cs);
    return true;
}


BOOL KillProcess(DWORD ProcessId)
{
    HANDLE hProcess=OpenProcess(PROCESS_TERMINATE,FALSE,ProcessId);
    if(hProcess==NULL)
        return FALSE;
    if(!TerminateProcess(hProcess,0))
        return FALSE;
    return TRUE;
}


bool RemoveContainerAll(unsigned dwFlags)
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
    bool bRet=AppContainer::AppContainerDelete(RemoveContainerAll);
    return bRet;
  }
};


DWORD ContainerRPCService(LPVOID)
{
    if(ContainerRemoteProcedureCall())
        return 1;
    return 0;
}



ContainerService::ContainerService():keepAlive(false)
{
    InitializeCriticalSection(&g_cs);
}
bool ContainerService::Execute()
{
    Container container;
    bool bRet=true;
    if(!container.Initialize()){
        return false;
    }
    DWORD tId;
    HANDLE hThread=CreateThread(NULL, 0, ContainerRPCService, nullptr, 0, &tId);
    if(!hThread)
    {
        goto Stop;
    }
    bRet=Manager(tId);
Stop:
    container.Stop();
    return bRet;
}

bool ContainerService::Manager(unsigned id){
    if(id==0)
        return false;
    while(this->keepAlive)
    {
        Sleep(200);
    }
    return true;
}

void ContainerService::Destory()
{
    EnterCriticalSection(&g_cs);
    for(auto i:taskMap)
    {
        KillProcess(i.first);
    }
    taskMap.clear();
    LeaveCriticalSection(&g_cs);
}

ContainerService::~ContainerService()
{
    DeleteCriticalSection(&g_cs);
}