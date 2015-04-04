/****************************************************************************************************************
*   Phoenix Package Runtime Library
*   Note: utilcode
*   Data: 2015.04.05
*   Author: Force.Charlie
*   E-mail: forcemz@outlook.com
*   Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifndef PHOENIX_PACKAGERUNTIME_H
#define PHOENIX_PACKAGERUNTIME_H
#include "rtdefs.h"
#include <stdbool.h>


typedef void* StringBufferEx;
typedef void* StackEx;

PKG_BEGIN_DECL
PKGEXTERN StringBufferEx StringBufferNew();
PKGEXTERN void StringBufferDelete(StringBufferEx *buffer);
PKGEXTERN bool StringBufferAppend(StringBufferEx buffer,const char* str, size_t strLen);
PKGEXTERN const char *StringBufferCStr(StringBufferEx buffer);
PKG_END_DECL

#endif
