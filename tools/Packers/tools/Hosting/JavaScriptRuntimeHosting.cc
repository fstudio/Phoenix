/*********************************************************************************************************
* JavaScriptRuntimeHosting.cc
* Note: Phoenix Container Runtime for JavaScript
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
//// when WIN SDK >WINBLUE
#if defined(_WIN32_WINNT) &&_WIN32_WINNT>0x0603
#define USE_EDGEMODE_JSRT
#endif

///
#include <jsrt.h>
#ifdef USE_EDGEMODE_JSRT
#pragma comment(lib,"chakrart.lib")
#else
#pragma comment(lib,"jsrt.lib,")
#endif

class JavaScriptRuntimeHost{
public:
    JavaScriptRuntimeHost();
    bool Run(const wchar_t *szJsfile);
    bool RunWithBuffer(char* buffer,size_t bufferSize);
};

JavaScriptRuntimeHost::JavaScriptRuntimeHost()
{
    ///
    //Resource Initilaize
}

bool JavaScriptRuntimeHost::Run(const wchar_t *szJsFile)
{
    return true;
}
