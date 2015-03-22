/*********************************************************************************************************
* ContainerService.cpp
* Note: Phoenix Container Service Manager
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"


class ContainerService{
private:
    bool BindPorts()
    {
        return true;
    }
public:
    ContainerService()
    {
        //
    }
    static bool ContainerServiceStart()
    {
        return 0;
    }
};

DWORD ContainerServiceManagerThread(LPVOID lParam)
{
    if(lParam==nullptr)
        return 1;
    ContainerService *sevice=reinterpret_cast<ContainerService *>(lParam);
    return 0;
}



