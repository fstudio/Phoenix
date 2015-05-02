/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: Xml Parser
*   Date: 2015.01.13
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHONEIX_PACKAGE_RUNTIME_XML_H
#define PHONEIX_PACKAGE_RUNTIME_XML_H
#include "rtdefs.h"

typedef void* XmlResolve_t;
PKG_BEGIN_DECL
////Feature.
PKGEXTERN XmlResolve_t XmlResolveNew(const char *xmlbody);
PKGEXTERN XmlResolve_t XmlResolveLoader(const char *xmlfile);
PKGEXTERN void XmlResolveDelete(XmlResolve_t xrt);
PKGEXTERN bool GetAttribute(XmlResolve_t xrt,const char* element,const char* key,char* attribute);
PKGEXTERN bool GetElementText(XmlResolve_t xrt,const char* element, char* text);

PKGEXTERN bool GetForeachElementNamespaceText(XmlResolve_t xrt,
    const char* element,
    const char* nsp,
    char* text);

PKGEXTERN bool GetForeachNamespaceAttribute(XmlResolve_t xrt,
    const char* element,
    const char* nsp,
    const char* key,
    const char* ansp,
    char* text);

PKG_END_DECL


#endif