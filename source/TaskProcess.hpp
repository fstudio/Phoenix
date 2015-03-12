/*********************************************************************************************************
* TaskProcess.hpp
* Note: Phoenix Task Process
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_TASK_PROCESS_HPP
#define PHOENIX_TASK_PROCESS_HPP

#include <vector>
#ifndef _WINDOWS_
#include <Windows.h>
#endif

namespace Task{

class TaskProcess{
private:
    DWORD dwParent;
    bool SetParentProcess();
public:
    TaskProcess(int Argv,wchar_t *Argv);
    TaskProcess(std::vector<std::wstring> &Args);
    TaskProcess();
    int Execute();
};

}
#endif
