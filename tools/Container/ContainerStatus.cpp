/*********************************************************************************************************
* ContainerStatus.cpp
* Note: Phoenix Container Self Status Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include <stdlib.h>
#include <string>


bool LauncherSelfWithNonElevated()
{
    wchar_t szPath[32767]={0};
    std::wstring strCmdLine;
    HRESULT hr=S_OK;
    if(GetModuleFileNameW(nullptr,szPath,32767)==ERROR_INSUFFICIENT_BUFFER)
        return false;
    LPWSTR *szArgList;
    int argCount;
    szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
    for(int i=1;i<argCount;i++)
    {
        strCmdLine+=szArgList[i];
        strCmdLine+=+L" ";
    }
    LocalFree(szArgList);
    hr=ProcessLauncherWithNonElevated(szPath,strCmdLine.c_str(),nullptr);
    return hr==0;
}

int LauncherContainerStatChecker()
{
    int iRet=0;
    if(IsUserAnAdmin())
    {
        LauncherSelfWithNonElevated();
        iRet=1;
        return iRet;////
    }
    return 0;
}
