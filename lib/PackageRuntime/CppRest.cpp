/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: CppRest.cpp
*   Data: 2015.02.08
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/HTTP.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <Winhttp.h>
#include <wincrypt.h>
#include "CppRest.h"



inline const wchar_t *RemoveURLProtocolMark(const wchar_t *url,bool &isSSL)
{
    if(url==nullptr&&wcslen(url)<12)
        return nullptr;
    if(wcsncmp(L"http",url,4)!=0)//https://github.com http://github.com
        return nullptr;
    if(url[4]=='s'){
        isSSL=true;
        return &url[8];
    }
    isSSL=false;
    return &url[7];
}

static bool GetHostNameNoMark(const wchar_t* url,wchar_t *dest,wchar_t *subURL)
{
    dest[0]=url[0];
    while(*url!='\0'&&*url!='/')
    {
        *dest++=*url++;
    }
    dest='\0';
    wcscpy(subURL,url);
    return true;
}

CppRest::CppRest():hConnect(nullptr),hSession(nullptr),hRequest(nullptr),useAgent(L"PkgCppRest/1.0")
{
    //
}
CppRest::~CppRest()
{
    if(hConnect)
        WinHttpCloseHandle(hConnect);
    if(hSession)
        WinHttpCloseHandle(hSession);
    if(hRequest)
        WinHttpCloseHandle(hRequest);
}

/*
std::string HttpRequest(char * lpHostName,short sPort,char * lpUrl,char * lpMethod,char * lpPostData,int nPostDataLen)
{
    HINTERNET hInternet,hConnect,hRequest;

    BOOL bRet;

    std::string strResponse;

    hInternet = (HINSTANCE)InternetOpen("User-Agent",INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
    if(!hInternet)
        goto Ret0;

    hConnect = (HINSTANCE)InternetConnect(hInternet,lpHostName,sPort,NULL,"HTTP/1.1",INTERNET_SERVICE_HTTP,0,0);
    if(!hConnect)
        goto Ret0;

    hRequest = (HINSTANCE)HttpOpenRequest(hConnect,lpMethod,lpUrl,"HTTP/1.1",NULL,NULL,INTERNET_FLAG_RELOAD,0);
    if(!hRequest)
        goto Ret0;

    //bRet = HttpAddRequestHeaders(hRequest,"Content-Type: application/x-www-form-urlencoded",Len(FORMHEADERS),HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
    //if(!bRet)
        //goto Ret0;

    bRet = HttpSendRequest(hRequest,NULL,0,lpPostData,nPostDataLen);
    while(TRUE)
    {
        char cReadBuffer[4096];
        unsigned long lNumberOfBytesRead;
        bRet = InternetReadFile(hRequest,cReadBuffer,sizeof(cReadBuffer) - 1,&lNumberOfBytesRead);
        if(!bRet || !lNumberOfBytesRead)
            break;
        cReadBuffer[lNumberOfBytesRead] = 0;
        strResponse = strResponse + cReadBuffer;
    }

 Ret0:
    if(hRequest)
        InternetCloseHandle(hRequest);
    if(hConnect)
        InternetCloseHandle(hConnect);
    if(hInternet)
        InternetCloseHandle(hInternet);

    return strResponse;
}
*/




extern "C" PKGEXTERN char *SendRequest()
{
    return nullptr;
}

