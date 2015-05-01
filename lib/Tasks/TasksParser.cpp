/*********************************************************************************************************
* TasksParser.cpp
* Note: Phoenix Editor  TasksParser
* Data: 2015.05.01
* E-mail:<forcemz@outlook.com>
* Author: Force  Charlie
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <rapidjson/rapidjson.h>
#include <string>

////task file $workspaceRoot/tasks.json
class TasksExecution{
private:
    std::string cmd;
    std::string args;
};