/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note:  XmlResolve.cpp
*   Date: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/XML.h>
#include "tinyxml2.h"
#include <string>

using namespace tinyxml2;

extern "C" PKGEXTERN  XmlResolve_t XmlResolveNew(const char *xmlbody)
{
    XMLDocument *doc=new XMLDocument();
    doc->Parse(xmlbody);
    if(doc->ErrorID()!=0)
    {
        delete doc;
        return nullptr;
    }
    return doc;
}

extern "C" PKGEXTERN XmlResolve_t XmlResolveLoader(const char *xmlfile)
{
    XMLDocument *doc=new XMLDocument();
    doc->LoadFile(xmlfile);
    if(doc->ErrorID()!=0)
    {
        delete doc;
        return nullptr;
    }
    return doc;
}

extern "C" PKGEXTERN void XmlResolveDelete(XmlResolve_t xrt)
{
    //
    if(xrt==nullptr)
        return ;
    XMLDocument *doc=reinterpret_cast<XMLDocument *>(xrt);
    delete doc;
}
extern "C" PKGEXTERN bool GetAttribute(XmlResolve_t xrt,const char* element,const char* key,char* attribute)
{
    XMLDocument *doc=reinterpret_cast<XMLDocument *>(xrt);
    XMLElement *scene=doc->RootElement();
    XMLElement *surface=scene->FirstChildElement(element);
    strcpy(attribute,surface->Attribute(key));
    return true;
}
extern "C" PKGEXTERN bool GetElementText(XmlResolve_t xrt,const char* element, char* text)
{
    XMLDocument *doc=reinterpret_cast<XMLDocument *>(xrt);
    XMLElement  *scene=doc->RootElement();
    XMLElement *surface=scene->FirstChildElement(element);
    strcpy(text,surface->GetText());
    return true;
}
extern "C" PKGEXTERN bool GetForeachElementNamespaceText(XmlResolve_t xrt,const char* element,const char* nsp,char* text)
{
     XMLDocument *doc=reinterpret_cast<XMLDocument *>(xrt);
    std::string nelement=std::string(element);
    nelement+=":";
    nelement+=nsp;
    XMLElement *scene=doc->RootElement();
    XMLElement *surface=scene->FirstChildElement(nelement.c_str());
    strcpy(text,surface->GetText());
    return true;
}
extern "C" PKGEXTERN bool GetForeachNamespaceAttribute(XmlResolve_t xrt,
    const char* element,
    const char* nsp,
    const char* key,
    const char* ansp,
    char* text)
{
    XMLDocument *doc=reinterpret_cast<XMLDocument *>(xrt);
    std::string nelem=element;
    if(nsp!=nullptr)
    {
        nelem+=":";
        nelem+=nsp;
    }
    std::string attr=key;
    if(ansp!=nullptr){
        attr+=":";
        attr+=ansp;
    }
    XMLElement *scene=doc->RootElement();
    XMLElement *surface=scene->FirstChildElement(nelem.c_str());
    strcpy(text,surface->Attribute(attr.c_str()));
    return true;
}
//////////Write Options.


