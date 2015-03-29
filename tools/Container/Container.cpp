/*********************************************************************************************************
* Container.cpp
* Note: Phoenix Container
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include "ContainerAPI.h"
#include "ContainerServiceHub.hpp"

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  int ret=0;
  if((ret=LauncherContainerStatChecker())!=0)
    return ret;
  ContainerService containerService;
  if(!containerService.Execute())
    ret=1;
  containerService.Destory();
  return ret;
}

