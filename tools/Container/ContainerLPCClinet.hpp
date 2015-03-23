//+------------------------------------------------------------------------------------------------------
// ContainerLPCClient.hpp
// Note: Phoenix Container
// E-mail:<forcemz@outlook.com>
// Data: @2015.03
// Copyright (C) 2015 The ForceStudio All Rights Reserved.
//+------------------------------------------------------------------------------------------------------
#ifndef CONTAINER_LPC_CLIENT_API_HPP
#define CONTAINER_LPC_CLIENT_API_HPP
#include <Windows.h>

int WINAPI LauncherWithLPC(LPCWSTR pszApp,
    LPCWSTR pszArgs,
    LPCWSTR pszDir);

#endif
