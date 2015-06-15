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

static volatile LONG g_keepAlive=1;
static volatile LONG clientNum=0;


bool InterlockedExchangeAddEx(bool model)
{
    if(model)
    {
        InterlockedExchangeAdd(&clientNum,1);
    }
    else
    {
        if(clientNum>0)
        {
            InterlockedExchangeAdd(&clientNum,-1);
        }
    }
    return true;
}

unsigned LookAccessClientSize()
{
    return clientNum;
}

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

void ContainerStopKeepAlive()
{
    InterlockedExchange(&g_keepAlive,0);
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


bool RemoveContainerTask(unsigned dwFlags)
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
    return (AppContainerProfileInitialize()==S_OK);
  }
  bool Stop() {
    CoUninitialize();
    bool bRet=DeleteAppContainerProfileRestricted(RemoveContainerTask);
    return bRet;
  }
};


DWORD WINAPI ContainerRPCService(LPVOID)
{
    if(ContainerRemoteProcedureCall())
        return 1;
    return 0;
}



ContainerService::ContainerService(Parameters &param):m_param(param)
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
    while(g_keepAlive)
    {
        ///MessageBoxW(nullptr,L"SSS",L"Manager",MB_OK);
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
