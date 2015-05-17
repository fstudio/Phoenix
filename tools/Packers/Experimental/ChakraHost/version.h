/*********************************************************************************************************
* version.h
* Note: Phoenix Packers RunScript
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_PACKERS_RUNSCRIPT_VERSION_H
#define PHOENIX_PACKERS_RUNSCRIPT_VERSION_H

#define TOSTR_(a) L#a
#define TOSTR(a) TOSTR_(a)
#define TOSTRING(str) TOSTR(str)

#define NOW_YEAR 2015
#define TOOLS_MARJO_VERSION   1
#define TOOLS_MINJO_VERSION    0
#define TOOLS_PATCH_VERSION   0
#define TOOLS_BUILD_VERSION  100

#define VERSION_STRING   TOSTRING(TOOLS_MARJO_VERSION.TOOLS_MINJO_VERSION.TOOLS_PATCH_VERSION.TOOLS_BUILD_VERSION)
#define VERSION_WORDS  TOOLS_MARJO_VERSION,TOOLS_MINJO_VERSION,TOOLS_PATCH_VERSION,TOOLS_BUILD_VERSION

#define COPYRIGHT L"Copyright \xA9"
#define RESERVEDINFO " The Force Studio.All Rights Reserved."
#define YEARSTRING TOSTR(NOW_YEAR)

#endif
