/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: JSON
*   Date: 2015.01.13
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_JSON_H
#define PHOENIX_PACKAGE_RUNTIME_JSON_H
#include "rtdefs.h"

typedef void*  JSONResolve_t;


PKG_BEGIN_DECL
////Feature.
PKGEXTERN JSONResolve_t JSONResolveNew(const char *jsonText);
PKGEXTERN bool JSONResolveNewEx(JSONResolve_t *pjt,const char *jsonText);
PKGEXTERN bool JSONResolveGetKV(const char* key,char *value,JSONResolve_t jt);
PKGEXTERN void JSONResolveDelete(JSONResolve_t jt);
PKG_END_DECL


#endif