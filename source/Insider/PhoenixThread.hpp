/*********************************************************************************************************
* PhoenixThread.hpp
* Note: Phoenix Thread
* Date: 2015.01
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_THREAD_HPP
#define PHOENIX_THREAD_HPP
#include <Windows.h>
#include <functional>

typedef DWORD (WINAPI *ThreadCallBack)(LPVOID lpThreadParameter);


class PhoenixThread{
private:
    DWORD IdOfThread;
    LPVOID m_param;
    HANDLE hThread;
    bool IsRunOnce;
    ThreadCallBack m_eFunc;
public:
    PhoenixThread(ThreadCallBack efunc,LPVOID param);
    unsigned GetThreadObjectId(){return this->IdOfThread;}
    bool Run();
    bool Suspend();
    bool Resume();
    bool Exit();
};

#endif
