/*********************************************************************************************************
* SearchWindowSelf.cpp
* Note: Phoenix Search Window Self
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/

#include <Windows.h>
#include "UIWindow.h"
#include <string>

HWND WINAPI GetSelfClassActiveWindowHwnd()
{
    HWND hWnd=FindWindowW(nullptr,UIWINDOWCLASS);
    /*
    Checker Mutex
    */
    //if Window Enable and Visible
    if(IsWindow(hWnd)&&IsWindowVisible(hWnd)){
        return hWnd;
    }
    return nullptr;
}

bool WINAPI TellActiveWindowOpenFile(HWND hWnd,std::wstring file)
{
    return true;
}

bool WINAPI TellActiveWindowOpenFileCstr(HWND hWnd,const wchar_t *filestr)
{
    return true;
}
