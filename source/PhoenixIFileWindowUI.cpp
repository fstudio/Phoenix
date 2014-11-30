/*********************************************************************************************************
* PhoenixIFileWindowUI.cpp
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: IShell Common Dialog.
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strsafe.h>
#include "PhoenixUI.h"
#ifndef UNC_MAX_PATH
#define UNC_MAX_PATH 32767
#endif


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PhoenixIFileWindowUI::PhoenixIFileWindowUI(HWND hParent):m_hParent(hParent)
{
    this->windowTitle=L"Phoenix IFileWindow";
}


bool PhoenixIFileWindowUI::IFileOpenWindow(/*Out*/const wchar_t *ofile)
{
    //wcscpy_s(ofile,UNC_MAX_PATH,L"\\\\?\\");
    //wcscat_s()
    return true;
}

bool PhoenixIFileWindowUI::IFileSaveWindow(/*Out*/const wchar_t *sfile)
{
    //wcscpy_s(sfile,UNC_MAX_PATH,L"\\\\?\\");//add UNC prefix
    return true;
}

bool PhoenixIFileWindowUI::GetFileNameFromOpenWindow(std::wstring *ofile,bool IsSelectUNC)
{
    WCHAR szfile[UNC_MAX_PATH]={0};
    if(IsSelectUNC)
    {
        if(this->IFileOpenWindowModeUNC(szfile))
            {
                *ofile=szfile;
                return true;
            }
    }else{
        if(this->IFileOpenWindow(szfile))
        {
            *ofile=szfile;
            return true;
        }
    }
    *ofile=L"Note: Not Select File or Function Error.";
    return false;
}

bool PhoenixIFileWindowUI::GetFileNameFromSaveWindow(std::wstring *sfile,bool IsSelectUNC)
{
    WCHAR szfile[UNC_MAX_PATH]={0};
    if(IsSelectUNC)
    {
        if(this->IFileSaveWindowModeUNC(szfile))
            {
                *sfile=szfile;
                return true;
            }
    }else{
        if(this->IFileSaveWindow(szfile))
        {
            *sfile=szfile;
            return true;
        }
    }
    *sfile=L"Note: Not Create File Name or Function Error.";
    return false;
}

//////UNC PATH

bool PhoenixIFileWindowUI::IFileOpenWindowModeUNC(/*Out*/const wchar_t *ofile)
{
    return true;
}

bool PhoenixIFileWindowUI::IFileSaveWindowModeUNC(/*Out*/const wchar_t *sfile)
{
    return true;
}


