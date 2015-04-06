/*********************************************************************************************************
* ContainerJobManager.cpp
* Note: Phoenix Container Service JobObject Manager
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include <string>
#include "ContainerJobManager.hpp"

const wchar_t *ContainerHostJobObjectName = L"Phoenix.Container.JobObject.APIv1\0";

ContainerJobManager::ContainerJobManager():hJob(nullptr)
{
  ///
}
ContainerJobManager::~ContainerJobManager()
{
  ///
}
bool ContainerJobManager::Initialize()
{
  BOOL bInJob=FALSE;
  IsProcessInJob(GetCurrentProcess(),NULL,&bInJob);
  if(bInJob)
  {
    //Debug Message: This Process already in a job
    return false;
  }
  return true;
}
void ContainerJobManager::Destory()
{
  if(!hJob)
  {
    this->hJob=OpenJobObject(READ_CONTROL,FALSE,ContainerHostJobObjectName);
    if(!this->hJob)
      return ;
  }
  TerminateJobObject(hJob,1);
}
HRESULT ContainerJobManager::StartRestrictedProcessEx(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszWorkdir,DWORD &pid)
{
  ///
  //OpenJobObject
  HANDLE hJob=OpenJobObject(READ_CONTROL,FALSE,ContainerHostJobObjectName);
  ///CreateProcess(...);
  return 0;
}

HRESULT ContainerJobManager::StartRestrictedProcess(LPCWSTR pszApp,LPCWSTR pszArgs,LPCWSTR pszWorkdir)
{
  DWORD m_pid=0;
  return ContainerJobManager::StartRestrictedProcessEx(pszApp,pszArgs,pszWorkdir,m_pid);
}

