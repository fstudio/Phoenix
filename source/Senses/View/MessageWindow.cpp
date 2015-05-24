/*********************************************************************************************************
* MessageWindow.cpp
* Note: Phoenix TaskWindow
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "MessageWindow.hpp"
#include <Shellapi.h>
#include <commctrl.h>
#include <comdef.h>
#include <taskschd.h>



static HICON gMwIcon=nullptr;
static bool runOnce=false;

static HICON TryGetApplicationIcon()
{
    if (gMwIcon || runOnce)
        return gMwIcon;
    //SHGetFileInfo get Application ICON
    SHFILEINFO shfi;
    HICON hIcon;
    wchar_t szApp[32678] = { 0 };
    GetModuleFileNameW(nullptr, szApp, 32678);
    hIcon = (HICON) SHGetFileInfoW(
        szApp,
        0,
        &shfi,
        sizeof(SHFILEINFO),
        SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_ICON);
    if (hIcon)
    {
        gMwIcon = hIcon;
    }
    runOnce = true;
    return gMwIcon;
}
HRESULT CALLBACK
TaskWindowCallBackProc(
__in HWND hwnd,
__in UINT msg,
__in WPARAM wParam,
__in LPARAM lParam,
__in LONG_PTR lpRefData
)
{
    switch (msg)
    {
    case TDN_CREATED:
        ::SetForegroundWindow(hwnd);
        break;
    case TDN_RADIO_BUTTON_CLICKED:
        break;
    case TDN_BUTTON_CLICKED:
        break;
    case TDN_HYPERLINK_CLICKED:
        ShellExecuteW(hwnd, NULL, (LPCWSTR) lParam, NULL, NULL, SW_SHOWNORMAL);
        break;
    }

    return S_OK;
}

//////////////////
MessageWindowImpl::MessageWindowImpl(HWND hParent,std::wstring &title,
    std::wstring &note,
    std::wstring &content,
    std::wstring &info,
    int errorLevel)
:m_hParent(hParent),
m_title(title),
m_note(note),
m_content(content),
m_ninfo(info),
errorlevel(errorLevel),
m_hIcon(nullptr)
{
    ////
}

bool MessageWindowImpl::InitializeWindowImpl()
{
    int nButton=0;
    int nRadioButton=0;
    TASKDIALOGCONFIG tdConfig;
    memset(&tdConfig, 0, sizeof(tdConfig));
    tdConfig.cbSize = sizeof(tdConfig);
    tdConfig.hwndParent = this->m_hParent;
    tdConfig.hInstance = GetModuleHandle(nullptr);
    tdConfig.dwFlags =TDF_ALLOW_DIALOG_CANCELLATION |
    TDF_EXPAND_FOOTER_AREA |
    TDF_POSITION_RELATIVE_TO_WINDOW|
    TDF_ENABLE_HYPERLINKS;
    tdConfig.nDefaultRadioButton = nRadioButton;

    tdConfig.pszWindowTitle =this->m_title.empty()?nullptr:this->m_title.c_str();
    tdConfig.pszMainInstruction = this->m_note.empty()?nullptr:this->m_note.c_str();
    tdConfig.pszContent =this->m_content.empty()?nullptr:this->m_content.c_str();
    switch(errorlevel)
    {
        case ERROR_LEVEL_FLAGS::WARNING_LEVEL:
        tdConfig.pszMainIcon=TD_WARNING_ICON;
        break;
        case ERROR_LEVEL_FLAGS::ERROR_LEVEL:
        tdConfig.pszMainIcon=TD_ERROR_ICON;
        break;
        case ERROR_LEVEL_FLAGS::SHIELD_LEVEL:
        tdConfig.pszMainIcon=TD_SHIELD_ICON;
        break;
        case ERROR_LEVEL_FLAGS::NORMAL_LEVEL:
        default:
        tdConfig.pszMainIcon=TD_INFORMATION_ICON;
        break;
    }
    if(this->m_hIcon)
    {
        tdConfig.hMainIcon=static_cast<HICON>(this->m_hIcon);
        tdConfig.dwFlags |= TDF_USE_HICON_MAIN;
    }
    /*else if((TryGetApplicationIcon()!=nullptr)
    {
        tdConfig.hMainIcon=static_cast<HICON>(TryGetApplicationIcon());
        tdConfig.dwFlags |= TDF_USE_HICON_MAIN;
    }*/
    tdConfig.pszExpandedInformation =m_ninfo.c_str();

    tdConfig.pszCollapsedControlText = L"More information";
    tdConfig.pszExpandedControlText = L"Less information";
    tdConfig.pfCallback = TaskWindowCallBackProc;
    this->hr = TaskDialogIndirect(&tdConfig, &nButton, &nRadioButton, NULL);
    return true;
}
bool MessageWindowImpl::SetMainIcon(HICON hIcon)
{
    if(hIcon)
        this->m_hIcon=hIcon;
    return true;
}
HRESULT MessageWindowImpl::Show()
{
    InitializeWindowImpl();
    return this->hr;
}
///
HRESULT MessageWindowImpl::MessageWindowShow(HWND hParent,
    std::wstring &titleText,
    std::wstring &note,
    std::wstring &content,
    std::wstring &info,
    int errorLevel)
{
    MessageWindowImpl  wimpl(hParent,titleText,note,content,info,errorLevel);
    return wimpl.Show();
}

HRESULT MessageWindowImpl::MessageWindowShowCStr(HWND hParent,
    LPCWSTR titleText,
    LPCWSTR note,
    LPCWSTR content,
    LPCWSTR info,
    int errorLevel)
{
    int nButton=0;
    int nRadioButton=0;
    HRESULT hr=S_OK;
    TASKDIALOGCONFIG tdConfig;
    memset(&tdConfig, 0, sizeof(tdConfig));
    tdConfig.cbSize = sizeof(tdConfig);
    tdConfig.hwndParent = hParent;
    tdConfig.hInstance = GetModuleHandle(nullptr);
    tdConfig.dwFlags =TDF_ALLOW_DIALOG_CANCELLATION |
    TDF_EXPAND_FOOTER_AREA |
    TDF_POSITION_RELATIVE_TO_WINDOW|
    TDF_ENABLE_HYPERLINKS;
    tdConfig.nDefaultRadioButton = nRadioButton;

    tdConfig.pszWindowTitle =titleText;
    tdConfig.pszMainInstruction = note;
    tdConfig.pszContent =content;
    switch(errorLevel)
    {
        case ERROR_LEVEL_FLAGS::WARNING_LEVEL:
        tdConfig.pszMainIcon=TD_WARNING_ICON;
        break;
        case ERROR_LEVEL_FLAGS::ERROR_LEVEL:
        tdConfig.pszMainIcon=TD_ERROR_ICON;
        break;
        case ERROR_LEVEL_FLAGS::SHIELD_LEVEL:
        tdConfig.pszMainIcon=TD_SHIELD_ICON;
        break;
        case ERROR_LEVEL_FLAGS::NORMAL_LEVEL:
        default:
        tdConfig.pszMainIcon=TD_INFORMATION_ICON;
        break;
    }
    tdConfig.pszExpandedInformation =info;

    tdConfig.pszCollapsedControlText = L"More information";
    tdConfig.pszExpandedControlText = L"Less information";
    tdConfig.pfCallback = TaskWindowCallBackProc;
    return TaskDialogIndirect(&tdConfig, &nButton, &nRadioButton, NULL);;
}