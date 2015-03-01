/*********************************************************************************************************
* MessageWindow.hpp
* Note: Phoenix TaskWindow
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_MESSAGEWINDOW_HPP
#define PHOENIX_MESSAGEWINDOW_HPP
#include <string>
#include <Windows.h>

class MessageWindowImpl{
public:
    enum ERROR_LEVEL{
        MW_NORMAL_WINDOW=0,
        MW_WARNING_WINDOW=1,
        MW_ERROR_WINDOW=2
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
    static HRESULT MessageWindowShow(HWND hParent,std::wstring &titleText,std::wstring &note,std::wstring &content,std::wstring &info,int errorLevel=0);//Default is zero
};

#endif
