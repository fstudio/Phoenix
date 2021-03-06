/*********************************************************************************************************
* Arguments.hpp
* Note: Phoenix CommandLine Arguments
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef COMMANDLINEARGUMENTS_HPP
#define COMMANDLINEARGUMENTS_HPP
#pragma once
#include <string>
#include <vector>


enum OptionLevel{
    OptionLevel_Normal=0x0000,
    OptionLevel_Foreground=0x0001,
    OptionLevel_Version=0x0002,
    OptionLevel_Usage=0x0004,
    OptionLevel_Reset=0x0008,
    OptionLevel_Setting=0x0010,
    OptionLevel_Init=0x0020,
    OptionLevel_New=0x0040,
    OptionLevel_UNKNOWN=0xF000
};

enum InstanceLevel{
    InstanceLevel_UI=1,
    InstanceLevel_Task=2
};

//-Profile with setting profile
struct ProcessParameters{
    int cmdMode;////CMD md is mutex.
    int taskMode;////is
    bool isProfile;
    std::wstring profile;
    std::vector<std::wstring> vfile;
    std::vector<std::wstring> unknowns;
};
bool ArgumentsFlow(ProcessParameters &pparam,bool isStoreUnknownOptions=false);


#endif
