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

#ifdef __cplusplus
class CppRest{
private:
    unsigned method;
    unsigned timeout;
    std::wstring useAgent;
    HINTERNET hSession;
    HINTERNET hConnect;
    HINTERNET hRequest;
    bool OpenConnet();
public:
    CppRest();
    ~CppRest();
    bool RequestSend(unsigned md,bool isSSL,const wchar_t url,wchar_t* stream,size_t streamLen,short port=80);
};

#endif



#endif
