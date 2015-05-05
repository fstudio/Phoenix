/*********************************************************************************************************
* SeekLauncher.cc
* Note: Phoenix Container Runtime
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
const LauncherHostTarget launcherTable[]={
    {0,0,0}
};

const int sizeOfTable=sizeof(launcherTable)/sizeof(LauncherHostTarget);

bool GetLauncherArgs(int index,const wchar_t *addArgs,std:::wstring &fullArgs)
{
    if(index>sizeOfTable)
        return false;
    ///
    return true;
}