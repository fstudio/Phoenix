/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: Base64
*   Date: 2015.02.07
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PACKAGERUNTIME_BASE64ENCOD_H
#define PACKAGERUNTIME_BASE64ENCOD_H
#include "rtdefs.h"



PKG_BEGIN_DECL
PKGEXTERN char *Base64Encode(const char* raw,size_t len,size_t *outlen);
PKGEXTERN char *Base64Decode(const char *data,size_t len,size_t *outlen);
PKGEXTERN void Base64StringFree(char* p);
PKG_END_DECL



#endif


