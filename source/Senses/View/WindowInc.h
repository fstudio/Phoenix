/*********************************************************************************************************
* WindowInc.h
* Note: Phoenix Window UI Defined
* Date: @2015.06
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef _SENSES_VIEW_WINDOWINC_
#define _SENSES_VIEW_WINDOWINC_
#include <Windows.h>
#include <atlbase.h>
#include <atlwin.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <atlsimpstr.h>
#include <ShlObj.h>
#include <d2d1.h>

#include <Resource.h> ///add resource

#define UIWINDOWCLASS L"Phoenix.UI.Core.Window.Render.v1"
#define EDITOR_RENDER_CLASSW L"Phoenix.Senses.InputSink.Render"

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+  Note , Windows Modern (Windows Runtime base Modern App)
+  based on the traditional model Win32
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define FRAMEWINDOW_STYLE  WS_CAPTION|WS_POPUP|WS_MINIMIZE|WS_CLIPSIBLINGS|WS_SYSMENU|\
WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX

#define FRAMEWINDOWEX_STYLE WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|\
WS_EX_WINDOWEDGE|WS_EX_NOREDIRECTIONBITMAP


#define INPUTSINK_STYLE WS_CHILDWINDOW|WS_VISIBLE
#define INPUTSINKEX_STYPE WS_EX_LEFT|WS_EX_LTRREADING|WS_EX_RIGHTSCROLLBAR|WS_EX_LAYERED|\
WS_EX_NOREDIRECTIONBITMAP



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



#endif
