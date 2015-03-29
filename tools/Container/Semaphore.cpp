/*********************************************************************************************************
* Semaphore.cpp
* Note: Phoenix Container Semaphore
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include "Semaphore.hpp"

DWORD WINAPI SemaphoreWaitThread(LPVOID lParam)
{
    //WaitMulitObjectSignal
    HANDLE hSemaphore=CreateSemaphoreW(NULL,4,4,CONTAINER_SEMAPHORE_NAME);
    return 0;
}