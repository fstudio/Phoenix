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

namespace Phoenix {
enum CONTAINER_PROCESS_RUNLEVEL {
  CONTAINER_INVOKER_RLEVEL = 0,
  CONTAINER_MANDATORY_INTEGRITY_CONTROL_RLEVEL = 1,
  CONTAINER_UAC_MEDIUM_RLEVEL = 2,
  CONTAINER_APPCONTAINER_RLEVEL=3
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
HRESULT WINAPI ProcessLauncherWithAppContainer(LPCWSTR exePath,
   LPCWSTR cmdArgs,
   LPCWSTR workDirectory);
HRESULT WINAPI ProcessLauncherExplorerLevel(LPCWSTR exePath,
    LPCWSTR cmdArgs,
    LPCWSTR workDirectory);
HRESULT WINAPI ProcessLauncherNonElevatedWithTaskSchd(LPCWSTR pszPath,
    LPCWSTR pszParameters,
    LPCWSTR pszDirectory);
bool LauncherSelfWithNonElevated();
int LauncherContainerStatChecker();

bool InitializeLogger();
void LoggerDestory();
void LogOut(FILE *fp,const wchar_t* format,...);
void LogOutDefault(const wchar_t* format,...);

int ContainerRemoteProcedureCall();

#endif
