/*********************************************************************************************************
* Mutex.cpp
* Note: Phoenix Mutex
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Header.hpp"

bool PhoenixCreateMutex()
{
    HANDLE hMutex = CreateMutexW(NULL, FALSE, L"PhoenixMutex+UIChannel");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        return false;
    }
    return true;
}

bool PhoenixRadio()
{
    return true;
}

