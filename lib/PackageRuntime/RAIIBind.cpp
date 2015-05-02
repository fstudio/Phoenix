/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: RAII
*   Date: 2015.01.14
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <map>
#include <Runtime/Runtime.h>



class Reference{
private:
    typedef void *PointerT;
private:
    std::map<int,PointerT> referencePointer;
public:
    Reference()
    {
        ////InitRefernce
    }
    ~Reference()
    {
        for(auto k:referencePointer)
        {
            delete k.second;
        }
    }
    int PushPointer(PointerT Ptr)
    {
        auto ret=referencePointer.insert(std::pair<int, PointerT>(referencePointer.size(),Ptr));
        if(ret.second)
            return (referencePointer.size()-1);
        return -1;
    }
};

extern "C" PKGEXTERN ReferenceT ReferenceInitialize()
{
    Reference *ref=new Reference();
    if(ref)
        return ref;
    return nullptr;
}

extern "C" PKGEXTERN void ReferenceDestory(ReferenceT ref)
{
    if(ref)
        delete ref;
}

extern "C" PKGEXTERN int ReferencePush(ReferenceT ref,void * Ptr)
{
    if(!ref)
        return -1;
    Reference *Ref=reinterpret_cast<Reference *>(ref);
    return Ref->PushPointer(Ptr);
}