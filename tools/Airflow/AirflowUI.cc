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
#include <CommCtrl.h>
#include <iostream>
#include <Shlwapi.h>

static const wchar_t * stdioimage()
{
    static WCHAR szTemp[MAX_PATH]={0};
    GetTempPathW(MAX_PATH,szTemp);
    wcscat_s(szTemp,MAX_PATH,L"Airflow.Standrand.IO.API.v1.log");
    return szTemp;
}

class RedirectStdIO{
private:
    bool isOpen;
public:
    RedirectStdIO()
    {
        FILE *stream;
        auto err=_wfreopen_s(&stream,stdioimage(),L"w+t", stdout);
        err=_wfreopen_s(&stream,stdioimage(),L"w",stderr);
        if(err==0)
            isOpen=true;
    }
    ~RedirectStdIO()
    {
        ////
        fflush(stdout);
        fclose(stdout);
        fclose(stderr);
    }
};

const LPCWSTR PackageSubffix[] = {L".msu", L".msi", L".cab"};
std::vector<std::wstring> vFileList;
#define MAXPAGES 5

INT_PTR WINAPI WindowMessageProcess(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    UNREFERENCED_PARAMETER(wParam);
    AirflowStructure *pdata = (AirflowStructure *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    WCHAR szPackagePath[4096]={0};
    WCHAR szRecover[4096]={0};
    switch(uMsg)
    {
        case WM_INITDIALOG:
        {
            PROPSHEETPAGE *psp = (PROPSHEETPAGE *)lParam;
            pdata = (AirflowStructure *)(psp->lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (DWORD_PTR)pdata);
            ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
            ChangeWindowMessageFilter(WM_COPYDATA, MSGFLT_ADD);
            ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
            PropSheet_ShowWizButtons(hWnd,0,
                PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH|PSWIZB_CANCEL);
            if(!pdata->rawfile.empty())
            {
                SetWindowTextW(GetDlgItem(hWnd,IDC_EDIT_FILEURL),pdata->rawfile.c_str());
            }
            if(!pdata->outdir.empty())
            {
                 SetWindowTextW(GetDlgItem(hWnd,IDC_EDIT_FOLDER),pdata->outdir.c_str());
            }
            DragAcceptFiles(hWnd, TRUE);
        }
        break;
        case WM_COMMAND:{
            switch (LOWORD(wParam)){
                case IDC_BUTTON_OPENFILE:
                {
                    std::wstring file;
                    auto ret=AirflowFileOpenWindow(hWnd,file,L"Open Installer and Update Package");
                    if(ret){
                        HWND hOEdit=GetDlgItem(hWnd,IDC_EDIT_FILEURL);
                        SetWindowTextW(hOEdit,file.c_str());
                        ////toCheck file type
                        std::wcout<<file<<std::endl;
                    }
                }
                break;
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
                case IDC_BUTTON_ENTER:
                {
                    SendDlgItemMessage(hWnd,IDC_PROCESS_RATE,PBM_SETPOS ,50,0L);
                    GetWindowText(GetDlgItem(hWnd,IDC_EDIT_FILEURL),szPackagePath,4096);
                    GetWindowText(GetDlgItem(hWnd,IDC_EDIT_FOLDER),szRecover,4096);
                    if(CheckPackageAfterLayout(szPackagePath,4096,szRecover,4096)){
                        AirflowTaskData *data=new AirflowTaskData();
                        data->isForce=false;
                        data->sendRate=true;
                        data->uMsgid=WM_ASYNCHRONOUS_NOTIFY_MSG;
                        data->hWnd=hWnd;
                        data->mRate=IDC_PROCESS_RATE;
                        data->rawfile=szPackagePath;
                        data->outdir=szRecover;
                        DWORD tId;
                        HANDLE hThread=CreateThread(NULL, 0, AirflowZendMethod, data, 0, &tId);
                        if(!hThread){
                            MessageBoxW(hWnd,L"CreateThread Failed",L"Error",MB_OK);
                        }else{
                            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_ENTER),FALSE);
                            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENDIR),FALSE);
                            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENFILE),FALSE);
                            EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FOLDER),FALSE);
                            EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FILEURL),FALSE);
                        }
                    }else{
                    //MessageBoxW(hWnd,)
                    //ShellExecuteW(hWnd,L"open",stdioimage(),NULL,NULL,SW_SHOW);
                    }
                }
                break;
                case IDC_BUTTON_CANCEL:
                {
                    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_ENTER),TRUE);
                    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENDIR),TRUE);
                    EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENFILE),TRUE);
                    EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FOLDER),TRUE);
                    EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FILEURL),TRUE);
                    ///Kill Thread and Delete Resource
                    SendDlgItemMessage(hWnd,IDC_PROCESS_RATE,PBM_SETPOS ,0,0L);
                }
                break;
                default:
                break;
            }
        }
        break;
        case WM_ASYNCHRONOUS_NOTIFY_MSG:
        {
            ///En
            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_ENTER),TRUE);
            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENDIR),TRUE);
            EnableWindow(GetDlgItem(hWnd,IDC_BUTTON_OPENFILE),TRUE);
            EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FOLDER),TRUE);
            EnableWindow(GetDlgItem(hWnd,IDC_EDIT_FILEURL),TRUE);
        }
        break;
        case WM_DROPFILES:
        {
            HDROP hDrop = (HDROP)wParam;
            UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
            WCHAR strFileName[MAX_PATH];
            for (UINT i = 0; i < nFileNum; i++)
            {
                DragQueryFileW(hDrop, i, strFileName, MAX_PATH);
                if(PathFindSuffixArrayW(strFileName,PackageSubffix,ARRAYSIZE(PackageSubffix)))
                {
                    vFileList.push_back(strFileName);
                }
                std::cout<<vFileList.size()<<std::endl;
                if(!vFileList.empty()){
                    SetWindowTextW(GetDlgItem(hWnd,IDC_EDIT_FILEURL),vFileList[0].c_str());
                }
            }
            DragFinish(hDrop);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
        case WM_NOTIFY:
        break;
        default:
        break;
    }
    return 0;
}


int AirflowUIChannel(AirflowStructure &cArgs)
{
    if(cArgs.cmdMode==CMD_PRINT_VERSION)
    {
        ///
        MessageBoxW(nullptr,AIRFLOW_VERSION_MARK,L"Airflow version box",MB_OK|MB_ICONINFORMATION);
    }else if(cArgs.cmdMode==CMD_PRINT_USAGE)
    {
        MessageBoxW(nullptr,AIRFLOW_USAGE_STRING_GUI,L"Airflow usage:",MB_OK|MB_ICONINFORMATION);
    }
    RedirectStdIO redirectIo;
    PROPSHEETPAGEW   psp;
    HPROPSHEETPAGE  rhpsp[MAXPAGES];
    ZeroMemory(&psp,sizeof(psp));
    ZeroMemory(&rhpsp, sizeof(HPROPSHEETPAGE)*MAXPAGES);
    psp.dwSize=sizeof(psp);
    psp.dwFlags=PSP_DEFAULT | PSP_USEHEADERTITLE | PSP_USEHEADERSUBTITLE;
    psp.lParam=(LPARAM) &cArgs;;
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
        psh.dwFlags         = PSH_AEROWIZARD ;
        psh.pszCaption      = L"Airflow -Recover Windows Installer and Update File";
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