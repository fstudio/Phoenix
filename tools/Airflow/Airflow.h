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
#include <vector>

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

#define MAX_PATH_WITH_UNC 32767 //32*1024 -1

#define AIRFLOW_VERSION_MARK L"Airflow-1.0.0.1"

#define AIRFLOW_USAGE_STRING L"Airflow Recover Windows Installer and Update Package\n\
Usage: Airflow [options]\n\
    -console\tRun Airflow with Console Mode\n\
    -help\tPrint Help and Exit(cui mode)\n\
    -version\tPrint Airflow version and exit(cui mode)\n\
    -debug\tRun Airflow with Debug Mode\n\
    -File\tSet Open Installer or Update Package name\n\
    -Out\tSet Extract Folder\n"

#define AIRFLOW_USAGE_STRING_GUI L"Airflow Recover Windows Installer and Update Package\n\
Usage: Airflow [options]\n\
    -console\tRun Airflow with Console Mode\n\
    -help\t\tPrint Help and Exit(cui mode)\n\
    -version\tPrint Airflow version and exit(cui mode)\n\
    -debug\tRun Airflow with Debug Mode\n\
    -File\t\tSet Open Installer or Update Package name\n\
    -Out\t\tSet Extract Folder\n"


enum FileTPE{
    FILETPE_UNKNOWN=0,///PM_INSTALLSHIELD_CAB
    FILETPE_MSINSTALLDB=1,//PM_MICROSOFT_INSTALLER_DB
    FILETPE_MSZIPCAB=2,//PM_MICROSOFT_CAB_MSZIP PM_MICROSOFT_CAB_NTCAB
    FILETPE_WINLZA=3//PM_MICROSOFT_CAB_LZ
};


struct AirflowStructure{
    int uiMode;/// msi or msu or cab
    int cmdMode;///Run some Task
    std::wstring rawfile;
    std::wstring outdir;
    std::vector<std::wstring> filelsit;
};

struct AirflowTaskData{
    bool isForce;
    bool sendRate;
    UINT uMsgid;
    HWND hWnd;
    int mRate;
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

///Asynchronous Notify Message Id
#define WM_ASYNCHRONOUS_NOTIFY_MSG WM_APP+1

UINT WINAPI RecoverMicrosoftStandaloneUpdatePackage(const wchar_t *szPackagePath,wchar_t *szRecoverPath);
UINT WINAPI RecoverCABPackage(const wchar_t *szPackagePath,const wchar_t *szRecoverPath);
UINT WINAPI RecoverInstallerPackage(const wchar_t *szPackagePath,const wchar_t *szRecoverPath);
UINT WINAPI RecoverInstallerPackageWithDB(const wchar_t *szPackagePath,const wchar_t *szRecoverPath);
bool WINAPI CheckPackageAfterLayout(wchar_t *szPackagePath, size_t pksize, wchar_t *szRecover, size_t resize);

typedef UINT(WINAPI* RecoverFunction)(const wchar_t*,const wchar_t*);

typedef struct RecoverRoute{
    int reId;
    RecoverFunction action;
}RecoverRoute;





#endif

