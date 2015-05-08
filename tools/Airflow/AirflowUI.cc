/*********************************************************************************************************
* Airflow.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"
#include "resource.h"
#include <Prsht.h>

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif


#define MAXPAGES 5
typedef struct
{
    BOOL fIsBoxChecked; //The state of the first interior page's check box
    BOOL fIsButtonClicked; //The state of the first interior page's group box
    //other shared data added here
} SHAREDWIZDATA;


INT_PTR WINAPI WindowMessageProcess(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    UNREFERENCED_PARAMETER(wParam);
    SHAREDWIZDATA *pdata = (SHAREDWIZDATA *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            PROPSHEETPAGE *psp = (PROPSHEETPAGE *)lParam;
            pdata = (SHAREDWIZDATA *)(psp->lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (DWORD_PTR)pdata);
        }
        break;
        case WM_COMMAND:
        switch (LOWORD(wParam)){
            case IDC_BUTTON_OPENFILE:
            {
                std::wstring file;
                auto ret=AirflowFileOpenWindow(hWnd,file,L"Open Installer and Update Package");
                if(ret){
                    HWND hOEdit=GetDlgItem(hWnd,IDC_EDIT_FILEURL);
                    SetWindowTextW(hOEdit,file.c_str());
                    ////toCheck file type
                }
            }break;
            case IDC_BUTTON_OPENDIR:
            {
                std::wstring folder;
                auto ret=AirflowFolderOpenWindow(hWnd,folder,L"Open Installer and Update Package");
                if(ret){
                    HWND hOEdit=GetDlgItem(hWnd,IDC_EDIT_FOLDER);
                    SetWindowTextW(hOEdit,folder.c_str());
                    ////toCheck file type
                }
            }
            break;
            default:
            break;
        }
        break;
        case WM_NOTIFY:
        break;
        case WM_CLOSE:
        break;
        default:
        break;
    }
    return 0;
}


int AirflowUIChannel(AirflowStructure &cArgs)
{
    PROPSHEETPAGEW   psp;
    HPROPSHEETPAGE  rhpsp[MAXPAGES];
    SHAREDWIZDATA   wizdata;
    ZeroMemory(&psp,sizeof(psp));
    ZeroMemory(&rhpsp, sizeof(HPROPSHEETPAGE)*MAXPAGES);
    psp.dwSize=sizeof(psp);
    psp.dwFlags=PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.lParam=(LPARAM) &wizdata;;
    psp.hInstance=GetModuleHandle(nullptr);
    psp.pszHeaderTitle=L"Select Your Install or Update Package";
    psp.pszTemplate=MAKEINTRESOURCE(IDD_AIRFLOW_FIRST);
    psp.pfnDlgProc=static_cast<DLGPROC>(WindowMessageProcess);
    rhpsp[0]           = CreatePropertySheetPage(&psp);
    if(rhpsp[0]){
        PROPSHEETHEADER psh;  //defines the property sheet
        ZeroMemory(&psh, sizeof(psh));
        psh.dwSize          = sizeof(psh);
        psh.hInstance       = GetModuleHandle(nullptr);
        psh.hwndParent      = NULL;
        psh.phpage          = rhpsp;
        psh.dwFlags         = PSH_AEROWIZARD | PSH_USEICONID;
        psh.pszCaption      = L"Airflow -Unpack Windows Installer and Update File";
        psh.pszIcon         = MAKEINTRESOURCE(IDI_WIZICON);
        psh.nStartPage      = 0;
        psh.nPages          = 1;
        if (PropertySheet(&psh) == -1){
            // an error occurred, call GetLastError() to retrieve it here.
            auto LastError=GetLastError();
            std::wstring failedError=L"GetLastError code: ";
            failedError=failedError+std::to_wstring(LastError);
            MessageBoxW(nullptr,failedError.c_str(),L"CreatePropertySheetPage Failed",MB_OK);
        }
    }else{
        DestroyPropertySheetPage(rhpsp[0]);
    }
    return 0;
}