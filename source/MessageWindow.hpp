/*********************************************************************************************************
* MessageWindow.hpp
* Note: Phoenix TaskWindow
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_MESSAGEWINDOW_HPP
#define PHOENIX_MESSAGEWINDOW_HPP
#include <string>
#include <Windows.h>

class MessageWindowImpl{
public:
    enum ERROR_LEVEL_FLAGS{
        NORMAL_LEVEL=0,
        WARNING_LEVEL=1,
        ERROR_LEVEL=2,
        SHIELD_LEVEL=3
    };
private:
    std::wstring m_title;
    std::wstring m_note;
    std::wstring m_content;
    std::wstring m_ninfo;
    int errorlevel;
    HWND m_hParent;
    HICON m_hIcon;
    bool InitializeWindowImpl();
    HRESULT hr;
public:
    MessageWindowImpl(HWND hParent,std::wstring &title,std::wstring &note,std::wstring &content,std::wstring &info,int errorLevel=0);
    bool SetMainIcon(HICON hIcon);
    HRESULT Show();
    static HRESULT MessageWindowShow(HWND hParent,
    std::wstring &titleText,
    std::wstring &note,
    std::wstring &content,
    std::wstring &info,
    int errorLevel=0);//Default is zero
    static HRESULT MessageWindowShowCStr(HWND hParent,
    LPCWSTR &titleText,
    LPCWSTR &note,
    LPCWSTR &content,
    LPCWSTR &info,
    int errorLevel=0);
};



#endif
