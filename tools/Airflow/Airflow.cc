/*********************************************************************************************************
* Airflow.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"


/**
*  CUI: airflow -console -File C:\\User\\hello\atshow.msi -u D:\\temp\\atshow
*  -File -Dir
**/
bool  ArgumentsGet(AirflowStructure &cArgs)
{
    int ac;
    LPWSTR *w_av = CommandLineToArgvW(GetCommandLineW(), &ac);
    for(int i=0;i<ac;i++)
    {
    }
    cArgs.uiMode=UI_MODE_GUI;
    LocalFree(w_av);
    return true;
}

int WINAPI wWinMain(HINSTANCE ,
    HINSTANCE ,
    LPWSTR cmdArgs,
    int nCmdShow)
{
    UNREFERENCED_PARAMETER(cmdArgs);
    UNREFERENCED_PARAMETER(nCmdShow);
    AirflowStructure cArgs;
    int ret=0;
    if(!ArgumentsGet(cArgs))
        return 1;
    if(cArgs.uiMode==UI_MODE_GUI) ///if run as gui
    {
        ret=AirflowUIChannel(cArgs);
    }else if(cArgs.uiMode==UI_MODE_CUI) /////if run as CUI
    {
        auto dwRet=AirflowZendMethodNonUI(cArgs);
        ret=static_cast<int>(dwRet);
    }else{
        return 2;
    }
    return 0;
}
