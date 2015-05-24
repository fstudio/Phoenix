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

bool WINAPI TellActiveWindowOpenFile(HWND hWnd,std::wstring &file)
{
    if(hWnd&&!file.empty())
    {
        ::PostMessage(hWnd,WM_COMMAND,(WPARAM)IDC_OPEN_FILE,(LPARAM)(file.c_str()));
    }
    return false;
}

bool WINAPI TellActiveWindowOpenFileCstr(HWND hWnd,const wchar_t *fstr)
{
    if(hWnd&&fstr)
    {
        ::PostMessage(hWnd,WM_COMMAND,(WPARAM)IDC_OPEN_FILE,(LPARAM)fstr);
    }
    return false;
}
