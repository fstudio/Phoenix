/*********************************************************************************************************
* Container.h
* Note: Phoenix Container Header
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_CONTAINER_CONTAINER_H
#define PHOENIX_CONTAINER_CONTAINER_H

#define TOSTR_(a) L#a
#define TOSTR(a) TOSTR_(a)
#define TOSTRING(str) TOSTR(str)

#define NOW_YEAR 2015
#define CONTAINER_MARJO_VERSION   1
#define CONTAINER_MINJO_VERSION    0
#define CONTAINER_PATCH_VERSION   0
#define CONTAINER_BUILD_VERSION  100

#define VERSION_STRING   TOSTRING(CONTAINER_MARJO_VERSION.CONTAINER_MINJO_VERSION.CONTAINER_PATCH_VERSION.CONTAINER_BUILD_VERSION)
#define VERSION_WORDS  CONTAINER_MARJO_VERSION,CONTAINER_MINJO_VERSION,CONTAINER_PATCH_VERSION,CONTAINER_BUILD_VERSION

#define COPYRIGHT L"Copyright © "
#define RESERVEDINFO " The Force Studio.All Rights Reserved."
#define YEARSTRING TOSTR(NOW_YEAR)

#endif
