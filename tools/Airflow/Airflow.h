/*********************************************************************************************************
* Airflow.h
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef AIRFLOW_H
#define AIRFLOW_H
#include <Windows.h>
#include <string>


#define UI_MODE_GUI  1
#define UI_MODE_CUI   2

#define CMD_NORMAL_WORKFLOW 0
#define CMD_PRINT_USAGE   1
#define CMD_PRINT_VERSION 2
#define CMD_WORKFLOW_DEBUG 3

#define PACKAGE_MAGIC_UNKNOWN 0
#define PM_MICROSOFT_INSTALLER_DB  1
#define PM_MICROSOFT_CAB_LZ 2
#define PM_MICROSOFT_CAB_MSZIP 3
#define PM_MICROSOFT_CAB_NTCAB 4
#define PM_INSTALLSHIELD_CAB 5




struct AirflowStructure{
    int uiMode;/// msi or msu or cab
    int cmdMode;///Run some Task
    std::wstring rawfile;
    std::wstring outdir;
};

struct AirflowTaskData{
    bool isForce;
    bool sendRate;
    UINT uMsgid;
    HWND hWnd;
    std::wstring rawfile;
    std::wstring outdir;
};

int AirflowUIChannel(AirflowStructure &cArgs);
DWORD WINAPI AirflowZendMethodNonUI(AirflowStructure &airflowst);
DWORD WINAPI AirflowZendMethod(LPVOID lParam);
bool AirflowFileOpenWindow(
    HWND hParent,
    std::wstring &filename,
    const wchar_t *pszWindowTitle=nullptr);

bool AirflowFolderOpenWindow(
    HWND hParent,
    std::wstring &folder,
    const wchar_t *pszWindowTitle=nullptr);

///Asynchronous report Message Id
extern UINT WM_ASYN_REPORT_MSG;


#endif

