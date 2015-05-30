/*********************************************************************************************************
* SeniorCore.cpp
* Note: Phoenix Senior Core
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include "Senses/Presenter/UIWindow.h"
#include <string>


int WINAPI SwitchSeniorCorePermissions(HWND hSelf)
{
    return 0;
}

int WINAPI LoseSeniorCorePermissions()
{
    return 0;
}

HRESULT WINAPI TryGetSeniorCorePermissions(HWND hDisplaySelf)
{
    if(hDisplaySelf==GetSelfClassActiveWindowHwnd()){
        ///Bind to Senior
    }
    return 0;
}

HWND WINAPI GetSelfClassActiveWindowHwnd()
{
    HWND hWnd=FindWindowW(nullptr,UIWINDOWCLASS);//ZOrder
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
