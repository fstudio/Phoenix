/*********************************************************************************************************
* UIWindow.hpp
* Note: UIWindow.hpp
* Date: @2015.01
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_UI_H
#define PHOENIX_UI_H

#define UIWINDOWCLASS L"Phoenix.UI.Window.Render.v1"
#include <atlbase.h>
#include <atlwin.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <atlsimpstr.h>
#include <d2d1.h>

#ifndef COMMAND_ID_HANDLER_SYSCMD
#define COMMAND_ID_HANDLER_SYSCMD(id, func) \
    if(uMsg == WM_SYSCOMMAND && id == LOWORD(wParam)) \
        { \
        bHandled = TRUE; \
        lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
        if(bHandled) \
            return TRUE; \
        }
#endif

////UI Tab
class UITab{
public:
    UITab();
    bool ReSize();
};


class UIWindow:public CWindowImpl<UIWindow, CWindow, CFrameWinTraits>{
private:
    size_t Id;
public:
    UIWindow();
    DECLARE_WND_CLASS(UIWINDOWCLASS)
    BEGIN_MSG_MAP(UIWindow)
        MESSAGE_HANDLER(WM_PAINT,OnPaint)
        MESSAGE_HANDLER(WM_CREATE,OnCreate)
        MESSAGE_HANDLER(WM_DESTROY,OnDestory)
        MESSAGE_HANDLER(WM_SIZE,OnSize)
    END_MSG_MAP()
    unsigned Runable();
private:
    std::vector<std::wstring> tab;
    bool InitializeUI();
    void ProcessMouseMessage(UINT message, LPARAM lParam);
public:
    HRESULT OnPaint(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnDestory(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
};

class IFileWindowUI{
public:
    IFileWindowUI();
};

class IFileOpenWindowUI:public IFileWindowUI{
public:
    IFileOpenWindowUI();
};

class IFileSaveWindowUI:public IFileWindowUI{
public:
    IFileSaveWindowUI();
};

#endif