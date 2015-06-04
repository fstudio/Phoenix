/*********************************************************************************************************
* WindowInc.h
* Note: Phoenix Window UI Defined
* Date: @2015.06
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef _SENSES_VIEW_WINDOWINC_
#define _SENSES_VIEW_WINDOWINC_

#include <atlbase.h>
#include <atlwin.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <atlsimpstr.h>
#include <ShlObj.h>
#include <d2d1.h>

#include <Resource.h> ///add resource

#define UIWINDOWCLASS L"Phoenix.UI.Window.Render.v1"
#define EDITOR_RENDER_CLASSW L"Phoenix.Senses.UI.Editor.Render"

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
