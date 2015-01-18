/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: JSON
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/JSON.h>

extern "C" PKGEXTERN JSONResolve_t JSONResolveNew(const char *jsonText)
{
    return nullptr;
}

extern "C"  PKGEXTERN bool JSONResolveNewEx(JSONResolve_t *pjt,const char *jsonText)
{
    if(pjt==nullptr)
        return false;
    return true;
}

extern "C" PKGEXTERN bool JSONResolveGet(const char* key,char *value)
{
    return 0;
}

extern "C" PKGEXTERN void JSONResolveDelete(JSONResolve_t jt)
{
    ///Delete this.
    if(jt==nullptr)
        return ;
    //
}
