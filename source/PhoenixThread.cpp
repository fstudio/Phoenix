/*********************************************************************************************************
* PhoenixThread.cpp
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note:
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>
#include "PhoenixThread.hpp"


PhoenixThread::PhoenixThread(ExecuteFunction efunc,LPVOID param):m_param(param),hThread(nullptr),
m_eFunc(efunc),
IdOfThread(0)
{

}
//Create a Thread
bool PhoenixThread::Run()
{
    hThread =static_cast<HANDLE>(CreateThread(NULL, 0, m_eFunc, m_param, 0, &IdOfThread));
    if(!hThread){
        return false;
    }
    IsRunOnce=true;
    return true;
}

bool PhoenixThread::Suspend()
{
    if(!hThread)
        return false;
    if(SuspendThread(hThread)==-1)
        return false;
    return true;
}

bool PhoenixThread::Resume()
{
    if(!hThread)
        return false;
    if(ResumeThread(hThread)==-1)
        return false;
    return true;
}

//Kill this Thread,do not it will hunk
bool PhoenixThread::Exit()
{
    ///HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, IdOfThread);
    if (hThread)
    {
        TerminateThread(hThread, 13);
        CloseHandle(hThread);
        return true;
    }
    hThread=nullptr;
    return false;
}

