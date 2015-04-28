/*********************************************************************************************************
* ChardetBindCodePage.cpp
* Thanks Mozilla Foundation
* @2015.04
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef _WIN32
#error "CodePage only support Windows NT"
#endif
#include <Windows.h>


int FindCodePageWithStr(const wchar_t *chardetStr)
{
    ASSERT(chardetStr);
}