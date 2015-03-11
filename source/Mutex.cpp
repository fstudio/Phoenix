/*********************************************************************************************************
* Mutex.cpp
* Note: Phoenix Mutex
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Header.hpp"

bool PhoenixCreateMutex()
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, _T("PhoenixMutex+UIChannel"));
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

