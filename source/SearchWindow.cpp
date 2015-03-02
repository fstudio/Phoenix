/*********************************************************************************************************
* SearchWindow.cpp
* Note: Phoenix Search Window
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
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
