/*********************************************************************************************************
* IFileWindowUI.cpp
* Note: IShell Common Dialog.
* Date: 2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Phoenix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <Uxtheme.h>
#include <tchar.h>
#include <strsafe.h>
#pragma warning(disable:4091)
#include <Shlwapi.h>
#include "Header.hpp"
#include "UIWindow.h"
#include "MessageWindow.hpp"

const wchar_t defaultSubffix[]=L".cpp";

const FilterSpec filterSpec[] =
{
    { L"Text File (*.txt;*.text;*.log)", L"*.txt;*.text;*.log" },
    { L"C++ Source File (*.cpp;*.c++;*.cxx;*.cc;*.h;*.h++;*.hpp)", L"*.cpp;*.c++;*.cxx;*.cc;*.h;*.h++;*.hpp" },
    { L"All Files (*.*)", L"*.*" }
};

void ReportErrorMessage(LPCWSTR pszFunction,HRESULT hr)
{
    const wchar_t *extMessage= _T("For more information about this tool, ")
        _T("Visit: <a href=\"https://github.com/forcegroup\">Force\xAEStudio</a>");
    wchar_t szBuffer[65535]={0};
    if(SUCCEEDED(StringCchPrintf(szBuffer,ARRAYSIZE(szBuffer),L"Call: %s Failed w/hr 0x%08lx ,Please Checker Error Code!",pszFunction,hr)))
    {
        MessageWindowImpl::MessageWindowShowCStr(nullptr,L"Call Function Failed",L"Failed information:",szBuffer,extMessage,2);
    }
}

const FilterSpec* getFilterSpecPointer(std::vector<FilterSpec> v)
{
    if(!v.empty())
        return &v[0];
    else
        return nullptr;
}


bool FileOpenWindowProvider(
    HWND hParent,
    std::wstring &filename,
    std::vector<FilterSpec> *vSuffix,
    const wchar_t *pszDefaultSuffix,
    const wchar_t *pszWindowTitle)
{
    HRESULT hr;
    bool bRet=false;
    CComPtr<IFileOpenDialog> pDlg;
    // Create the file-open dialog COM object.
    hr = pDlg.CoCreateInstance (__uuidof(FileOpenDialog));
    if (FAILED(hr)){
        ReportErrorMessage(L"FileOpenWindowProvider",hr);
        return false;
    }

    // Set the dialog's caption text and the available file types.
    // NOTE: Error handling omitted here for clarity.
    if(vSuffix){
        hr = pDlg->SetFileTypes(3,filterSpec);
    }else{
        hr = pDlg->SetFileTypes(vSuffix->size(),getFilterSpecPointer(*vSuffix));
    }
    pDlg->SetTitle(pszWindowTitle?pszWindowTitle:L"Open File Provider");
    pDlg->SetDefaultExtension(pszDefaultSuffix?pszDefaultSuffix:defaultSubffix);
    // Show the dialog.
    hr = pDlg->Show(hParent);
    if(SUCCEEDED(hr)){
        CComPtr<IShellItem> pItem;
        hr = pDlg->GetResult(&pItem);
        if(SUCCEEDED(hr))
        {
            PWSTR pwsz = NULL;
            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwsz);
            if(SUCCEEDED(hr))
            {
                filename=pwsz;
                bRet=true;
                CoTaskMemFree(pwsz);
            }
        }
    }
    return bRet;
}

///////////////////////////////////////////////Save File

bool FileSaveWindowProvider(
    HWND hParent,
    std::wstring &filename,
    std::vector<FilterSpec> *vSuffix,
    const wchar_t *pszDefaultSuffix,
    const wchar_t *pszDefaultFileName,
    const wchar_t *pszWindowTitle)
{
    HRESULT hr;
    bool bRet=false;
    CComPtr<IFileSaveDialog> pDlg;
    hr = pDlg.CoCreateInstance ( __uuidof(FileSaveDialog) );
    if ( FAILED(hr)){
        ReportErrorMessage(L"FileSaveWindowProvider",hr);
        return false;
    }
    // Set the dialog's caption text, file types, Save button label,
    // default file name, and default extension.
    // NOTE: Error handling omitted here for clarity.
    if(vSuffix){
        hr = pDlg->SetFileTypes(3,filterSpec);
    }else{
        hr = pDlg->SetFileTypes(vSuffix->size(),getFilterSpecPointer(*vSuffix));
    }
    pDlg->SetTitle(pszWindowTitle?pszWindowTitle:L"Save File Provider");
    pDlg->SetOkButtonLabel(L"D&o It!");
    pDlg->SetFileName(pszDefaultFileName?pszDefaultFileName:L"code.cpp");
    pDlg->SetDefaultExtension(pszDefaultSuffix?pszDefaultSuffix:defaultSubffix);
    // Show the dialog.
    hr = pDlg->Show (hParent);
    // If the user chose a file, save the user's data to that file.
    if(SUCCEEDED(hr)){
        CComPtr<IShellItem> pItem;
        hr = pDlg->GetResult (&pItem);
        if(SUCCEEDED(hr))
        {
            PWSTR pwsz = NULL;
            hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pwsz);
            if ( SUCCEEDED(hr)){
                filename=pwsz;
                CoTaskMemFree ( pwsz );
                bRet=true;
            }
        }
    }
    return bRet;
}



