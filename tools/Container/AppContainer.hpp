/*********************************************************************************************************
* AppContainer.hpp
* Note: Phoenix Container AppContainer
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef CONTAINER_APPCONTAINER_HPP
#define CONTAINER_APPCONTAINER_HPP

#ifndef _WINDOWS_
#include <Windows.h>
#endif
#include <functional>

bool DeleteAppContainerProfileRestricted(std::function<bool(unsigned)> rmTask);
HRESULT AppContainerProfileInitialize();
unsigned LauncherWithAppContainer(LPCWSTR pszApp,LPCWSTR cmdArgs,LPCWSTR workDir);
HRESULT LauncherWithAppContainerEx(LPCWSTR pszApp,LPCWSTR cmdArgs,LPCWSTR workDir,DWORD &pid);

#endif
