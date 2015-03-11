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

class Process{
public:
    Process(int Argv,wchar_t *Argv);
    Process(std::vector<std::wstring> Args);
};

#endif
