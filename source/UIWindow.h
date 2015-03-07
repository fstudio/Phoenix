/*********************************************************************************************************
* PhoenixUI.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: PhoenixUI header
* E-mail:<forcemz@outlook.com>
* @2014.09
**********************************************************************************************************/
#ifndef PHOENIX_UI_H
#define PHOENIX_UI_H

#define UIWINDOWCLASS L"Phoenix.UI.Window.Render.v1"
#include <atlbase.h>
#include <atlwin.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <atlsimpstr.h>

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
public:
    HRESULT OnPaint(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnCreate(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnDestory(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
    HRESULT OnSize(UINT nMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled);
};

class PhoenixIFileWindowUI{
private:
    HWND m_hParent;
    std::wstring windowTitle;
public:
    PhoenixIFileWindowUI(HWND hParent);
    void SetIFileWindowTitle(std::wstring wTitle);
    bool IFileOpenWindow(/*Out*/const wchar_t *ofile);
    bool IFileSaveWindow(/*Out*/const wchar_t *sfile);
    bool GetFileNameFromOpenWindow(std::wstring *ofile,bool IsSelectUNC);
    bool GetFileNameFromSaveWindow(std::wstring *sfile,bool IsSelectUNC);
private:
    unsigned CheckUNCPath();
public:
    bool IFileOpenWindowModeUNC(/*Out*/const wchar_t *ofile);
    bool IFileSaveWindowModeUNC(/*Out*/const wchar_t *sfile);
};

////UI Tab
class UITab{
public:
    UITab();
    bool ReSize();
};

#endif