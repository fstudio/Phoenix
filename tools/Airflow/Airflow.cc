/*********************************************************************************************************
* Airflow.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>


/**
*  CUI: airflow -console -file C:\\User\\hello\atshow.msi -u D:\\temp\\atshow
*
**/
bool  ArgumentsGet(AirflowStructure &cArgs)
{
    return true;
}

int WINAPI wWinMain(HINSTANCE ,
    HINSTANCE ,
    LPWSTR cmdArgs,
    int nCmdShow)
{
    AirflowStructure cArgs;
    int ret=0;
    if(!ArgumentsGet(cArgs))
        return 1;
    if(cArgs.uiMode==UI_MODE_GUI) ///if run as gui
    {
        ret=UIChannelProviders(cArgs);
    }else if(cArgs.uiMode==UI_MODE_CUI) /////if run as CUI
    {
        auto dwRet=AirflowZendMethodNonUI(cArgs);
        ret=static_cast<int>(dwRet);
    }else{
        return 2;
    }
    return 0;
}
