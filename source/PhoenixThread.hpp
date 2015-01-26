/*********************************************************************************************************
* PhoenixThread.hpp
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note:
* E-mail:<forcemz@outlook.com>
* @2015.01
**********************************************************************************************************/
#ifndef PHOENIX_THREAD_HPP
#define PHOENIX_THREAD_HPP
#include <Windows.h>
#include <functional>

class PhoenixThread{
private:
    unsigned IdOfThread;
    LPVOID m_param;
    HANDLE hThread;
    ExecuteFunction m_eFunc;
public:
    PhoenixThread(ExecuteFunction efunc,LPVOID param);
    unsigned GetThreadObjectId(){return this->IdOfThread;}
    bool Run();
    bool Suspend();
    bool Resume();
    bool Exit();
};

#endif
