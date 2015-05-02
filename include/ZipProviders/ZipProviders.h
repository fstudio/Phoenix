/*********************************************************************************************************
*   Phoenix ZipProviders Features
*   Note: ZipProviders.h
*   Date: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef ZIPPROVIDERS_H
#define ZIPPROVIDERS_H
#include <string>
#include <functional>
#include <Windows.h>
#include <ppltasks.h>


class ZipOptionRootEx{
protected:
    std::function<bool(std::wstring,int,void *)> NotifyFunction;
    void *clientPtr;
public:
    enum NotifyTypeEmun{
        NOTIFY_FAILD=0,
        NOTIFY_WARNING=1,
        NOTIFY_ASK=2,
        NOTIFY_TASK=3,
    };
    ZipOptionRootEx():clientPtr(nullptr)
    {
        ///
    }
    void SetNotifyFunction(std::function<bool(std::wstring,int,void *)> notifyFunc)
    {
        this->NotifyFunction=notifyFunc;
    }
    void SetClientPointer(void * Ptr)
    {
        this->clientPtr=Ptr;
    }
    virtual void AsynchronousProcess()=0;
    virtual bool ProcessContext()=0;
};

class ZipCompress:public ZipOptionRootEx{
private:
    std::wstring m_folder;
    std::wstring m_file;
public:
    ZipCompress(std::wstring &folder,std::wstring &file);
    void AsynchronousProcess();
    bool ProcessContext();
};

class ZipExtract:public ZipOptionRootEx{
private:
    std::wstring m_folder;
    std::wstring m_file;
public:
    ZipExtract(std::wstring &folder,std::wstring &file);
    void AsynchronousProcess();
    bool ProcessContext();
};

///////////////////////////////////////////////////////////////
/// int function(int status,void *date);
typedef int(*ProvidersCallBack)(bool ,void *);

bool ZipProvidersResolve(const char *dest,const char *source,ProvidersCallBack cb,void *date);
bool ZipProvidersCompress(const char *dest,const char *source,ProvidersCallBack cb,void *date);

#endif
