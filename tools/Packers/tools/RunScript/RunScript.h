/*********************************************************************************************************
* Hosting.h
* Note: Phoenix Container Runtime Header
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_CONTAINER_RUNTIME_HOSTING_H
#define PHOENIX_CONTAINER_RUNTIME_HOSTING_H
#include <Windows.h>


namespace JavaScript{
    int WINAPI RunScript(const wchar_t *szJsfile,const wchar_t *argument=nullptr);
    int WINAPI RunScriptBuffer(wchar_t* buffer,size_t bufferSize,const wchar_t *argument=nullptr);
}

#endif
