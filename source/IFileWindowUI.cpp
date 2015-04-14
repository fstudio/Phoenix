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
    HRESULT hr = S_OK;
    IFileDialog *pfd = NULL;
    bool bRet=false;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER,IID_PPV_ARGS(&pfd));
    if (SUCCEEDED(hr))
    {
        if (SUCCEEDED(hr)){
            hr = pfd->SetTitle(pszWindowTitle?pszWindowTitle:L"Open File Providers");
        }
        if (SUCCEEDED(hr)){
            if(vSuffix)
            {
                hr = pfd->SetFileTypes(3,filterSpec);
            }else{
                hr = pfd->SetFileTypes(vSuffix->size(),getFilterSpecPointer(*vSuffix));
            }
            if (SUCCEEDED(hr))
            {
                hr = pfd->SetFileTypeIndex(1);
            }
        }
        if (SUCCEEDED(hr)){
            hr = pfd->SetDefaultExtension(pszDefaultSuffix?pszDefaultSuffix:defaultSubffix);
        }
        if (SUCCEEDED(hr)){
            hr = pfd->Show(hParent);
            if (SUCCEEDED(hr)){
                IShellItem *psiResult = nullptr;
                hr = pfd->GetResult(&psiResult);
                if (SUCCEEDED(hr)){
                    PWSTR pszPath = nullptr;
                    hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
                    if (SUCCEEDED(hr)){
                        filename=pszPath;
                        bRet=true;
                        CoTaskMemFree(pszPath);
                    }
                    psiResult->Release();
                }
            }
        }
        pfd->Release();
    }
    if (FAILED(hr)){
        if (hr != HRESULT_FROM_WIN32(ERROR_CANCELLED)){
            ReportErrorMessage(L"FileOpenWindowProvider", hr);
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
    const wchar_t *pszWindowTitle)
{
    return true;
}



