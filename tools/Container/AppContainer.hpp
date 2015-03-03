/*********************************************************************************************************
* AppContainer.hpp
* Note: Phoenix Container AppContainer
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef CONTAINER_APPCONTAINER_HPP
#define CONTAINER_APPCONTAINER_HPP

#ifndef _WINDOWS_
#include <Windows.h>
#endif


class AppContainer{
private:
    static PSID appContainerSid;
public:
    static bool AppContainerInitialize();
    static void AppContainerClear();
protected:
    AppContainer(std::wstring app,std::wstring Args,);
    bool Exectue();
};

#endif
