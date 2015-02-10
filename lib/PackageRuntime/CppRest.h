/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: CppRest.h
*   Data: 2015.02.08
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_CPPREST_H
#define PHOENIX_PACKAGE_RUNTIME_CPPREST_H
#include <vector>
#ifdef __cplusplus

class CppRest{
public:
    enum ApiResult
    {
        CPPREST_API_200,
        CPPREST_API_401,
        CPPREST_API_403,
        CPPREST_USER_CANCEL,
        CPPREST_API_SERVERUNREACHABLE
    };
    struct MemPtrList{
        char *pointer;
        bool bfree;
        MemPtrList(char *p,bool b):pointer(p),bfree(b)
        {
            //
        }
    };
private:
    unsigned method;
    unsigned timeout;
    std::wstring useAgent;
    HINTERNET hSession;
    HINTERNET hConnect;
    HINTERNET hRequest;
    std::vector<MemPtrList> mpv;
    bool OpenConnet();
public:
    CppRest();
    ~CppRest();
    void SetUserAgent(std::wstring &ua);
    bool RequestSend(unsigned md,bool isSSL,const wchar_t url,wchar_t* stream,size_t streamLen,short port=80);
};

#endif



#endif
