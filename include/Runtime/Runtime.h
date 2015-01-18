/****************************************************************************************************************
* Phoenix Package Runtime Library
* Author:Force
* E-mail: forcemz@outlook.com
* Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifndef PHOENIX_PACKAGERUNTIME_H
#define PHOENIX_PACKAGERUNTIME_H
#include "rtdefs.h"
#include <stdbool.h>

typedef struct LauncherParam__{
    char moduleConfig[4096];
    char moduleParam[8192];
}LauncherParam;

PKG_BEGIN_DECL
///#include "HTTP.h"
PKGEXTERN bool ComponentInitialize();
PKGEXTERN void ComponentUnInitialze();
PKGEXTERN bool ComponentInitializeEx();
PKG_END_DECL

#endif
