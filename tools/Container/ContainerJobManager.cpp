/*********************************************************************************************************
* ContainerJobManager.cpp
* Note: Phoenix Container Service JobObject Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
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
  TreminateJobObject(hJob,1);
}
int ContainerJobManager::StartRestrictedProcess(LPCWSTR pszPath,LPCWSTR pszArgs,LPCWSTR pszWorkdir)
{
  ///
  //OpenJobObject
  HANDLE hJob==OpenJobObject(READ_CONTROL,FALSE,ContainerHostJobObjectName);
  return 0;
}
