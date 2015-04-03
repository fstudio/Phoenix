/*********************************************************************************************************
* UIWindow.cpp
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: UIWindow Window Class
* E-mail:<forcemz@outlook.com>
* @2015.01
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

#include "UIWindow.h"

UIWindow::UIWindow()
{

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
