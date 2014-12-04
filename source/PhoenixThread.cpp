/*********************************************************************************************************
* PhoenixThread.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note:
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>

class PhoenixThread{
private:
    unsigned tid;
    LPVOID m_param;
    PTHREADMAIN m_func;
public:
    PhoenixThread(PTHREADMAIN mfun,LPVOID param);
    bool Run();
    bool Exit();
};

PhoenixThread::PhoenixThread(PTHREADMAIN mfun,LPVOID param):m_param(param),
m_func(mfun),
tid(0)
{

}
//Create a Thread
bool PhoenixThread::Run()
{
    HANDLE hThread = CreateThread(NULL, 0, m_func, m_param, 0, &tid);
    if(!hThread){
        return false;
    }
    IsRunOnce=true;
    CloseHandle(hThread);
    return true;
}
//Kill this Thread
bool PhoenixThread::Exit()
{
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, tid);
    if (hProcess)
    {
            TerminateProcess(hProcess, 13);
            CloseHandle(hProcess);
    }
    return true;
}

