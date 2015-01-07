/*********************************************************************************************************
* PhoenixUI.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: PhoenixUI header
* E-mail:<forcemz@outlook.com>
* @2014.09
**********************************************************************************************************/
#ifndef PHOENIX_UI_H
#define PHOENIX_UI_H

#ifdef _WIN32
#define PHOENIXWINDOWCLASS L"Phoenix.UI.Window"
#define PHOENIXEDITWINDOWCLASS  L"Phoenix.UI.Edit.Window"

#endif


class PhoenixWindow{
private:
    size_t Id;
public:
    PhoenixWindow();
    unsigned Runable();
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
class PhoenixUITab{
public:
    PhoenixUITab();
    bool ReSize();
};

#endif