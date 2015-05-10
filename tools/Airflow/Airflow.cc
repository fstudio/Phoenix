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
    int Argc;
    cArgs.uiMode=UI_MODE_GUI;
    cArgs.cmdMode=CMD_NORMAL_WORKFLOW;
    bool Failed=false;
    int index=0;
    LPWSTR *Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
    for(int i=0;i<Argc;i++)
    {
        switch(Argv[i][0])
        {
            case '/':
            case '-':
            {
                if(wcslen(Argv[1])<2) break;
                if(_wcsicmp(&Argv[i][1],L"console")==0)
                {
                    cArgs.uiMode=UI_MODE_CUI;
                }else if(_wcsicmp(&Argv[i][1],L"help")==0){
                    cArgs.cmdMode=CMD_PRINT_USAGE;
                }else if(_wcsicmp(&Argv[i][1],L"version")==0){
                    cArgs.cmdMode=CMD_PRINT_VERSION;
                }else if(_wcsicmp(&Argv[i][1],L"debug")==0){
                    cArgs.cmdMode=CMD_WORKFLOW_DEBUG;
                }else if(_wcsicmp(&Argv[i][1],L"file")==0){
                    index=-1;
                    if(i<Argc-1)
                    {
                        cArgs.rawfile=Argv[i+1];
                    }
                }else if(_wcsicmp(&Argv[i][1],L"out")==0){
                    index=-1;
                    if(i<Argc-1)
                    {
                        cArgs.outdir=Argv[i+1];
                    }
                }else{
                    Failed=true;
                }
            }
            break;
            default:
            {
                if(Argc>1&&index>0)
                {
                    if(Argc==3){
                        switch(index)
                        {
                            case 0:
                            cArgs.rawfile=Argv[i];
                            index++;
                            break;
                            case 1:
                            cArgs.outdir=Argv[i];
                            index++;
                            break;
                            default:
                            break;
                        }
                    }else{
                        cArgs.filelsit.push_back(Argv[i]);
                    }
                }
            }
            break;
        }
    }
    LocalFree(Argv);
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
