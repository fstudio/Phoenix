/****************************************************************************************************************
* Phoenix Package Runtime Library MD5
* Author:Force
* E-mail: forcemz@outlook.com
* Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_MD5_H
#define PHOENIX_PACKAGE_RUNTIME_MD5_H
#include "rtdefs.h"
#include <stdint.h>
#include <stdbool.h>


PKG_BEGIN_DECL
PKGEXTERN void md5bin(const void *date,size_t len,unsigned char out[16]);
PKG_END_DECL


#endif
