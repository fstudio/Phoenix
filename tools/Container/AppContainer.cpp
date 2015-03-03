/*********************************************************************************************************
* AppContainer.cpp
* Note: Phoenix Container AppContainer
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "AppContainer.hpp"
#include <Userenv.h>
#pragma comment(lib,"Userenv")

PSID AppContainer::appContainerSid=nullptr;

bool AppContainer::AppContainerInitialize()
{
    wchar_t appContainerName[64]={0};
    wchar_t appContainerDisplayName[]=L"Phoenix.Container.AppContainer.v1\0";
    wchar_t appContainerDesc[2048];
    return 0;
}

void AppContainer::AppContainerClear()
{
    if(AppContainer::appContainerSid){
        FreeSid(AppContainer::appContainerSid)
        AppContainer::appContainerSid=nullptr;
    }
}