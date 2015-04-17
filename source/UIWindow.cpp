/*********************************************************************************************************
* UIWindow.cpp
* Note: UIWindow.cpp
* Date: @2015.01
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/

#define SECURITY_WIN32 1
#include <windowsx.h>
#include <dwmapi.h>
#include <Uxtheme.h>
#include <string>
#include <wincrypt.h>
#include <security.h>
#include <ShlDisp.h>
#include <Phoenix>
#include "Header.hpp"
#include "UIWindow.h"

UIWindow::UIWindow()
{

}

void UIWindow::ProcessMouseMessage()
{
    //
}

unsigned UIWindow::Runable()
{

    return 0;
}
bool UIWindow::InitializeUI()
{
    return true;
}
//////////UI Window Function

HRESULT UIWindow::OnPaint(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    return S_OK;
}
HRESULT UIWindow::OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    return S_OK;
}
HRESULT UIWindow::OnDestory(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    return S_OK;
}
HRESULT UIWindow::OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
    return S_OK;
}
