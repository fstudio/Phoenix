/*********************************************************************************************************
* Expand.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"
#include <Windows.h>
#include <lzexpand.h>
#include <setupapi.h>

UINT WINAPI RecoverMicrosoftStandaloneUpdatePackage(const wchar_t *szPackagePath,wchar_t *szRecoverPath)
{
    return 0;
}

UINT WINAPI RecoverCABPackage(const wchar_t *szPackagePath,wchar_t *szRecoverPath)
{
    UINT comp;
    wchar_t szPath[4096]={0};
    if(!SetupGetFileCompressionInfoExW(szPackagePath,szPath,sizeof(szPath),NULL,NULL,NULL,&comp))
    {
        wprintf(L"can't open input file %s\n",szPackagePath);
        return 1;
    }
    switch(comp)
    {
        case FILE_COMPRESSION_MSZIP:
        break;
        case FILE_COMPRESSION_WINLZA:
        break;
        default:
        break;
    }
    return 0;
}

