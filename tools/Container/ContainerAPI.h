/*********************************************************************************************************
* ContainerAPI.hpp
* Note: Phoenix Container API Header
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_CONTAINERAPI_H
#define PHOENIX_CONTAINERAPI_H
#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include <stdio.h>
#include <string>

namespace Phoenix {
enum CONTAINER_PROCESS_RUNLEVEL {
  CONTAINER_INVOKER_RLEVEL = 0,
  CONTAINER_MANDATORY_INTEGRITY_CONTROL_RLEVEL = 1,
  CONTAINER_UAC_MEDIUM_RLEVEL = 2,
  CONTAINER_APPCONTAINER_RLEVEL=3,
  CONTAINER_RUNINJOB=4
};
}
HRESULT WINAPI ProcessLauncher(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory,
  unsigned level);
HRESULT WINAPI ProcessLauncherWithNonElevated(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory);
HRESULT WINAPI ProcessLauncherMIC(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory);
HRESULT WINAPI ProcessLauncherExplorerLevel(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory);
HRESULT WINAPI ProcessLauncherNonElevatedWithTaskSchd(LPCWSTR pszPath,
  LPCWSTR pszParameters,
  LPCWSTR pszDirectory);
HRESULT WINAPI ProcessLauncherWithAppContainer(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory);

/*********************************************************************************************************************
* Function Ex, return code is this child process id. Zero is failed!
*********************************************************************************************************************/
unsigned WINAPI ProcessLauncherMICEx(LPCWSTR exePath,
  LPCWSTR cmdArgs,
  LPCWSTR workDirectory);


bool LauncherSelfWithNonElevated();
int LauncherContainerStatChecker();

bool InitializeLogger();
void LoggerDestory();
void TRACEWithFile(FILE *fp,const wchar_t* format,...);
void TRACE(const wchar_t* format,...);

int ContainerRemoteProcedureCall();
bool FindProcessFromContainer(unsigned pid);
bool ContainerProcessMapAtomAdd(unsigned pid,std::wstring appName);
bool RemoveContainerProcessId(unsigned pid);
void ContainerStopKeepAlive();
bool InterlockedExchangeAddEx(bool model);
unsigned LookAccessClientSize();


struct Parameters{
  bool focegournd;
  std::wstring profile;
};

#endif
