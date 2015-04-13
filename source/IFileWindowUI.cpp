/*********************************************************************************************************
* IFileWindowUI.cpp
* Note: IShell Common Dialog.
* Date: 2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Phoenix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strsafe.h>
#include "Header.hpp"
#include "UIWindow.h"

const wchar_t defaultSubffix[]=L"";

bool FileOpenWindowProvider(
    HWND hParent,
    std::wstring &filename,
    const wchar_t *pszSuffix ,
    const wchar_t *pszDefaultSuffix,
    const wchar_t pszWindow)
{
    return true;
}
bool FileSavaWindowProvider(
    HWND hParent,
    std::wstring &filename,
    const wchar_t *pszSuffix,
    const wchar_t *pszDefaultSuffix,
    const wchar_t *pszWindow)
{
    return true;
}



