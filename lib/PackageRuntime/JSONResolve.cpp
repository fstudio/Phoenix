/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: JSON
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/JSON.h>
#include "JSONResolveEx.hpp"

using namespace jsonxx;

extern "C" PKGEXTERN JSONResolve_t JSONResolveNew(const char *jsonText)
{
    std::string str=jsonText;
    Object *object=new Object();
    if(!object->parse(str))
    {
        delete object;
        return nullptr;
    }
    return object;
}

extern "C"  PKGEXTERN bool JSONResolveNewEx(JSONResolve_t *pjt,const char *jsonText)
{
    if(pjt==nullptr)
        return false;
    std::string str=jsonText;
    Object *object=new Object();
    if(!object->parse(str))
    {
        *pjt=nullptr;
        delete object;
        return false;
    }
    return true;
}

extern "C" PKGEXTERN bool JSONResolveGetKV(const char* key,char *value,JSONResolve_t jt)
{
    if(key==nullptr||value==nullptr||jt==nullptr)
        return false;
    Object *object=reinterpret_cast<Object *>(jt);
    if(object->has<String>(key))
    {
        strcpy(value,object->get<String>(key).c_str());
    }else{
        return false;
    }
    return true;
}

extern "C" PKGEXTERN void JSONResolveDelete(JSONResolve_t jt)
{
    ///Delete this.
    if(jt==nullptr)
        return ;
    delete jt;
    //
}
