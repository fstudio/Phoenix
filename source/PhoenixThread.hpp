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
