/*********************************************************************************************************
* ContainerStatus.cpp
* Note: Phoenix Container Self Status Manager
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include <stdlib.h>
#include <string>


bool LauncherSelfWithNonElevated(const wchar_t *pszcmdArgs)
{
    wchar_t szPath[32767]={0};
    std::wstring strCmdLine;
    HRESULT hr=S_OK;
    if(GetModuleFileNameW(nullptr,szPath,32767)==ERROR_INSUFFICIENT_BUFFER)
        return false;
    hr=ProcessLauncherWithNonElevated(szPath,pszcmdArgs,nullptr);
    return hr==0;
}

int LauncherContainerStatChecker(std::wstring &cmdArgs)
{
    int iRet=0;
    if(IsUserAnAdmin())
    {
        LauncherSelfWithNonElevated(cmdArgs.empty()?nullptr:cmdArgs.c_str());
        iRet=1;
        return iRet;////
    }
    return 0;
}
