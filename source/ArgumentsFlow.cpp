/*********************************************************************************************************
* ArgumentsFlow.hpp
* Note: Phoenix CommandLine Parser
* Date: @2015.05
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include "Arguments.hpp"



bool ArgumentsFlow(ProcessParameters &processParameters,bool isStoreUnknownOptions)
{
    int Argc;
    bool bNext=false;
    processParameters.cmdMode=OptionLevel_Normal;
    processParameters.taskMode=InstanceLevel_UI;
    LPWSTR *Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
    for(int i=1;i<Argc;i++)
    {
        switch(Argv[i][0])
        {
            case '/':
            case '-':
            {
                if(wcslen(Argv[1])<2) break;
                if(_wcsicmp(&Argv[i][1],L"Task")==0)
                {
                    ///cArgs.uiMode=UI_MODE_CUI;
                    processParameters.taskMode=InstanceLevel_Task;
                }else if(_wcsicmp(&Argv[i][1],L"Foreground")==0){
                    ///
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Foreground;
                }else if(_wcsicmp(&Argv[i][1],L"-version")==0){
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Version;
                }else if(_wcsicmp(&Argv[i][1],L"-help")==0){
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Usage;
                }else if(_wcsicmp(&Argv[i][1],L"Init")==0){
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Init;
                }else if(_wcsicmp(&Argv[i][1],L"Reset")==0){
                    ///
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Reset;
                }else if(_wcsicmp(&Argv[i][1],L"Setting")==0){
                    ///
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_Setting;
                }else if(_wcsicmp(&Argv[i][1],L"New")==0){
                    ///
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_New;
                }else if(_wcsicmp(&Argv[i][1],L"Profile")==0){
                    ///
                    //index=-1;
                    processParameters.isProfile=true;
                    if(i<Argc-1)
                    {
                        //cArgs.rawfile=Argv[i+1];
                        bNext=true;
                    }
                }else if(_wcsicmp(&Argv[i][1],L"File")==0){
                    if(i<Argc-1)
                    {
                        //cArgs.rawfile=Argv[i+1];
                        processParameters.vfile.push_back(Argv[i+1]);
                        bNext=true;
                    }
                }else{
                    processParameters.cmdMode=processParameters.cmdMode|OptionLevel_UNKNOWN;
                    if(isStoreUnknownOptions)
                    {
                        processParameters.unknowns.push_back(Argv[i]);
                    }
                }
            }
            break;
            default:
            {
                if(!bNext){
                    processParameters.vfile.push_back(Argv[i]);
                    //bNext=true;
                    }else{
                    bNext=false;
                    }
            }
            break;
        }
    }
    LocalFree(Argv);
    return true;
}
