/*********************************************************************************************************
*   Phoneix Plugin Runtime
*   Note: Zip
*   Date: 2015.01.15
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHONEIX_PACKAGE_RUNTIME_ZIP_H
#define PHONEIX_PACKAGE_RUNTIME_ZIP_H
#include "rtdefs.h"

typedef  int(*ZIP_CALLBACK)(char*);


PKG_BEGIN_DECL
////Feature.
PKGEXTERN int ComperssFolderFiles(const char* folder);
PKG_END_DECL

#endif