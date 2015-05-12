/*********************************************************************************************************
* ArgumentsFlow.hpp
* Note: Phoenix CommandLine Parser
* Date: @2015.05
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include "Arguments.hpp"



bool ArgumentsFlow(ArgumentsStructure &as,bool isStoreUnknownOptions)
{
    int Argc;
    bool bNext=false;
    as.cmdMode=OptionLevel_UNKNOWN;
    as.taskMode=InstanceLevel_UI;
    LPWSTR *Argv = CommandLineToArgvW(GetCommandLineW(), &Argc);
    for(int i=0;i<Argc;i++)
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
                    as.taskMode=InstanceLevel_Task;
                }else if(_wcsicmp(&Argv[i][1],L"Foreground")==0){
                    ///
                    as.cmdMode=as.cmdMode|OptionLevel_Foreground;
                }else if(_wcsicmp(&Argv[i][1],L"-help")==0){
                    as.cmdMode=as.cmdMode|OptionLevel_Usage;
                }else if(_wcsicmp(&Argv[i][1],L"-version")==0){
                    as.cmdMode=as.cmdMode|OptionLevel_Help;
                }else if(_wcsicmp(&Argv[i][1],L"Init")==0){
                    as.cmdMode=as.cmdMode|OptionLevel_Init;
                }else if(_wcsicmp(&Argv[i][1],L"Reset")==0){
                    ///
                    as.cmdMode=as.cmdMode|OptionLevel_Reset;
                }else if(_wcsicmp(&Argv[i][1],L"Setting")==0){
                    ///
                    as.cmdMode=as.cmdMode|OptionLevel_Setting;
                }else if(_wcsicmp(&Argv[i][1],L"New")==0){
                    ///
                    as.cmdMode=as.cmdMode|OptionLevel_New;
                }else if(_wcsicmp(&Argv[i][1],L"Profile")==0){
                    ///
                    //index=-1;
                    as.isProfile=true;
                    if(i<Argc-1)
                    {
                        //cArgs.rawfile=Argv[i+1];
                        bNext=true;
                    }
                }else if(_wcsicmp(&Argv[i][1],L"File")==0){
                    if(i<Argc-1)
                    {
                        //cArgs.rawfile=Argv[i+1];
                        as.vfile.push_back(Argv[i+1]);
                        bNext=true;
                    }
                }else{
                    if(isStoreUnknownOptions)
                    {
                        as.unknowns.push_back(Argv[i]);
                    }
                }
            }
            break;
            default:
            {
                if(i>=1){
                    if(!bNext)
                    {
                        as.vfile.push_back(Argv[i]);
                        //bNext=true;
                    }else{
                        bNext=false;
                    }
                }
            }
            break;
        }
    }
    LocalFree(Argv);
    return true;
}
