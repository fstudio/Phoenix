/*********************************************************************************************************
* Msi.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"
#include <Windows.h>
#include <Msi.h>
#include <Msiquery.h>

/*
* UINT WINAPI RecoverInstallerPackage(const wchar_t *,const wchar_t*);
* Success return zero, other return error code.
*/


UINT WINAPI RecoverInstallerPackage(const wchar_t *szPackagePath,const wchar_t *szRecoverPath)
{
    //MsiConfigureProductExW
    //MsiInstallProduct()
    std::wstring td=L"TARGETDIR=";
    td+=szRecoverPath;
    MsiInstallProductW(szPackagePath,td.c_str());
    return 0;
}

UINT WINAPI RecoverInstallerPackageWithDB(const wchar_t *szPackagePath,const wchar_t *szRecoverPath)
{
    return 0;
}
