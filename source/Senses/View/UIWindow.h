/*********************************************************************************************************
* UIWindow.hpp
* Note: UIWindow.hpp
* Date: @2015.01
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_UI_H
#define PHOENIX_UI_H
#ifndef _SENSES_VIEW_WINDOWINC_
#include "WindowInc.h"
#endif
#include <string>
#include <vector>


/*
CalculatePopupWindowPosition

Calculate Popup Window Point

BOOL WINAPI CalculatePopupWindowPosition(
  _In_      const POINT *anchorPoint,
  _In_      const SIZE *windowSize,
  _In_      UINT flags,
  _In_opt_  RECT *excludeRect,
  _Out_     RECT *popupWindowPosition
);

URL:https://msdn.microsoft.com/en-us/library/windows/desktop/dd565861(v=vs.85).aspx


CreateWindowInBand  ////

CreateWindowIndirect
+...
HWND GUIAPI CreateMainWindowIndirect(PDLGTEMPLATE pDlgTemplate,HWND hOwner,WNDPROC WndProc);
BOOL GUIAPI DestroyMainWindowIndirect(HWND hMainWin);
...
UpdateLayeredWindowIndirect

BOOL WINAPI ChangeWindowMessageFilterEx(
  _In_         HWND hWnd,
  _In_         UINT message,
  _In_         DWORD action,
  _Inout_opt_  PCHANGEFILTERSTRUCT pChangeFilterStruct
);
URL:https://msdn.microsoft.com/en-us/library/windows/desktop/dd388202(v=vs.85).aspx

In Search Window.
UINT WINAPI GetWindowModuleFileName(
  _In_   HWND hwnd,
  _Out_  LPTSTR lpszFileName,
  _In_   UINT cchFileNameMax
);
Layout:
int MapWindowPoints(
  _In_     HWND hWndFrom,
  _In_     HWND hWndTo,
  _Inout_  LPPOINT lpPoints,
  _In_     UINT cPoints
);
*/


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

typedef COMDLG_FILTERSPEC FilterSpec;


bool FileOpenWindowProvider(
    HWND hParent,
    std::wstring &filename,
    std::vector<FilterSpec> *vSuffix,
    const wchar_t *pszDefaultSuffix,
    const wchar_t *pszWindowTitle);
bool FileSaveWindowProvider(
    HWND hParent,
    std::wstring &filename,
    std::vector<FilterSpec> *vSuffix,
    const wchar_t *pszDefaultSuffix,
    const wchar_t *pszDefaultFileName,
    const wchar_t *pszWindowTitle);


#endif