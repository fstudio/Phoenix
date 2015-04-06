/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: CppRest.cpp
*   Date: 2015.02.08
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/HTTP.h>
#include <cstdio>
#include <cstdint>
#include <Windows.h>
#include <string>
#include <Winhttp.h>
#include <wincrypt.h>
#include "CppRest.h"
#include "UriParser.h"

class wCharGet{
private:
    wchar_t *wstr;
public:
    wCharGet(const char *str):wstr(nullptr)
    {
        if(str==nullptr)
            return ;
        size_t len =strlen(str);
        int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
        if(unicodeLen==0)
            return ;
        this->wstr = new wchar_t[unicodeLen + 1];
        memset(this->wstr, 0, (unicodeLen + 1) * sizeof(wchar_t));
        ::MultiByteToWideChar(CP_ACP, 0,str, -1, (LPWSTR)this->wstr,unicodeLen);
    }
    const wchar_t *Get()
    {
        if(!wstr)
            return nullptr;
        return const_cast<const wchar_t *>(wstr);
    }
    ~wCharGet()
    {
        if(wstr)
            delete[] wstr;
    }
};

const wchar_t *GetMethodString(unsigned i)
{
    switch(i)
    {
        case HTTP_RQ_METHOD_GET:
        return L"GET";
        case HTTP_RQ_METHOD_HEAD:
        return L"HEAD";
        case HTTP_RQ_METHOD_POST:
        return L"POST";
        case HTTP_RQ_METHOD_PUT:
        return L"PUT";
        case HTTP_RQ_METHOD_DELETE:
        return L"DELETE";
        case HTTP_RQ_METHOD_OPTIONS:
        return L"OPTIONS";
        case HTTP_RQ_METHOD_TRACE:
        return L"TRACE";
        case HTTP_RQ_METHOD_CONNECT:
        return L"CONNECT";
        default:
        break;
    }
    return L"GET";
}

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
    *dest='\0';
    wcscpy(subURL,url);
    return true;
}

bool BaseURLResolve(const wchar_t *url,wchar_t *host,wchar_t *path,unsigned *port)
{
    //swscanf
    return 0;
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

bool CppRest::OpenConnet()
{
    this->hSession=WinHttpOpen(useAgent.c_str(),
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,0);
    if(this->hSession)
        return true;
    return false;
}

void CppRest::SetUserAgent(std::wstring &ua)
{
    this->useAgent=ua;
}


extern "C" PKGEXTERN Request_t RequestCreateNew()
{
    CppRest *cppRest=new CppRest();
    return cppRest;
}

extern "C" PKGEXTERN void RequestFree(Request_t rq)
{
    if(rq)
        delete reinterpret_cast<CppRest*>(rq);
}

extern "C" PKGEXTERN char *SendRequest(unsigned method,Request_t rq)
{
    return nullptr;
}

extern "C" PKGEXTERN void SetUserAgent(const char *ua,Request_t rq)
{
    if(rq==nullptr)
        return;
    CppRest *cppRest=reinterpret_cast<CppRest*>(rq);
    wCharGet wua(ua);
    std::wstring wuaStr=wua.Get();
    cppRest->SetUserAgent(wuaStr);
}


static char *PackageRuntimeStandardRequestW(const wchar_t *ua,
    const wchar_t *host,
    unsigned method,
    const wchar_t *url,
    size_t *bufferSize,
    bool useSSL=false)
{
    return nullptr;
}


extern "C" PKGEXTERN char *PackageRuntimeStandardRequest(const char *ua,
    const char *host,
    unsigned method,
    const char *url,
    size_t *bufferSize,
    bool useSSL)
{
    wCharGet wua(ua);
    wCharGet whost(host);
    wCharGet wurl(url);
    return PackageRuntimeStandardRequestW(wua.Get(),whost.Get(),method,wurl.Get(),bufferSize,useSSL);
}

extern "C" PKGEXTERN void RequestBufferFree(void *p)
{
    if(p)
      free(p);
}


static bool StandardRequestW(const wchar_t *ua,
    const wchar_t *host,
    unsigned method,
    const wchar_t *url,
    bool useSSL,
    ReceiveResponeCallBack recallback,
    void *dataPtr)
{
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL bResults = FALSE;
    HINTERNET hSession = NULL,
    hConnect = NULL,
    hRequest = NULL;
    INTERNET_PORT nPort = (useSSL) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;
    hSession = WinHttpOpen(ua,
        WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS, 0);

    if (hSession)
        hConnect = WinHttpConnect(hSession, host,
            nPort, 0);
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect,
            GetMethodString(method),
            url,
            NULL, WINHTTP_NO_REFERER,
            WINHTTP_DEFAULT_ACCEPT_TYPES,
            (useSSL)?WINHTTP_FLAG_SECURE:0);
    if (hRequest)
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,
            0, WINHTTP_NO_REQUEST_DATA, 0,
            0, 0);
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);
    if (bResults){
        do{
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",GetLastError());
            pszOutBuffer = new char[dwSize+1];
            ZeroMemory(pszOutBuffer, dwSize+1);
            if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,dwSize, &dwDownloaded)){
                printf("Error %u in WinHttpReadData.\n", GetLastError());
            }
            else{
                recallback(pszOutBuffer,dwSize,dataPtr);
            }
            delete[] pszOutBuffer;
        }while (dwSize > 0);
    }
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    return true;
}


extern "C" PKGEXTERN bool StandardRequest(const char *ua,
    const char *host,
    unsigned method,
    const char *url,
    bool useSSL,
    ReceiveResponeCallBack recallback,
    void *dataPtr)
{
    wCharGet wua(ua);
    wCharGet whost(host);
    wCharGet wurl(url);
    return StandardRequestW(wua.Get(),whost.Get(),method,wurl.Get(),useSSL,recallback,dataPtr);
}

static uint32_t
ToUInt32 (const char *s, uint32_t fail_value, int base, bool *success_ptr)
{
    if (s && s[0])
    {
        char *end = nullptr;
        const unsigned long uval = ::strtoul (s, &end, base);
        if (*end == '\0')
        {
            if (success_ptr)
                *success_ptr = (uval <= UINT32_MAX);
            return (uint32_t)uval; // All characters were used, return the result
        }
    }
    if (success_ptr) *success_ptr = false;
    return fail_value;
}


extern "C" PKGEXTERN bool StandardURLResolve(const char *uri,char *scheme,char *host,char *path,unsigned *ports)
{
    char port_buf[11]={0};
    char scheme_buf[100] = {0};
    path[0]='/';
        bool ok = false;
    if (4==sscanf(uri, "%99[^:/]://%255[^/:]:%10[^/]/%2047s", scheme_buf, host, port_buf, path+1)) { ok = true; }
    else if (3==sscanf(uri, "%99[^:/]://%255[^/:]:%10[^/]", scheme_buf, host, port_buf)) { ok = true; }
    else if (3==sscanf(uri, "%99[^:/]://%255[^/]/%2047s", scheme_buf, host, path+1)) { ok = true; }
    else if (2==sscanf(uri, "%99[^:/]://%255[^/]", scheme_buf, host)) { ok = true; }

    bool success = false;
    int port_tmp = -1;
    if (port_buf[0])
    {
        port_tmp = ToUInt32(port_buf, UINT32_MAX, 10, &success);
        if (!success || port_tmp > 65535)
        {
            // there are invalid characters in port_buf
            return false;
        }
        *ports=port_tmp;
    }else{
        *ports=URIGetPortFromSchemes(scheme_buf);
    }
    if(ok)
    {
        strcpy(scheme,scheme_buf);
    }
    return ok;
}
