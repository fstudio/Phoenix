/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: XmlLite.cpp
*   Data: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/XML.h>
#include "tinyxml2.h"

using namespace tinyxml2;

extern "C" PKGEXTERN  XmlResolve_t XmlResolveNew(const char *xmlbody)
{
    XMLDocument *doc=new XMLDocument();
    if(doc==nullptr)
        return nullptr;
    return doc;
}

extern "C" PKGEXTERN void XmlResolveDelete(XmlResolve_t xrt)
{
    //
    if(xrt==nullptr)
        return ;
    XMLDocument *doc=static_cast<XMLDocument *>(xrt);
    delete doc;
}
extern "C" PKGEXTERN bool GetAttribute(XmlResolve_t xrt,const char* element,const char* key,char* attribute)
{
    return true;
}
extern "C" PKGEXTERN bool GetElementText(XmlResolve_t xtr,const char* element, char* text)
{
    return true;
}
extern "C" PKGEXTERN bool GetForeachElementNamespaceText(XmlResolve_t xrt,const char* element,const char* nsp,char* text)
{
    return true;
}
extern "C" PKGEXTERN bool GetForeachNamespaceAttribute(XmlResolve_t xrt,const char* element,const char* nsp,const char* key,const char* ansp,char* text)
{
    return true;
}
