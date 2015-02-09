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

std::wstring MultiByteToUnicode(const std::string &str,unsigned cp) {
  int len = 0;
  len = str.length();
  int unicodeLen = ::MultiByteToWideChar(cp, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pUnicode;
  pUnicode = new wchar_t[unicodeLen + 1];
  memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
  ::MultiByteToWideChar(cp, 0, str.c_str(), -1, (LPWSTR)pUnicode,
                        unicodeLen);
  std::wstring rt;
  rt = (wchar_t *)pUnicode;
  delete pUnicode;

  return rt;
}
std::string UnicodeToMultiByte(const std::wstring &wstr,unsigned cp) {
  char *pElementText;
  int iTextLen;
  // wide char to multi char
  iTextLen =
      WideCharToMultiByte(cp, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
  pElementText = new char[iTextLen + 1];
  memset((void *)pElementText, 0, sizeof(char) * (iTextLen + 1));
  ::WideCharToMultiByte(cp, 0, wstr.c_str(), -1, pElementText, iTextLen,
                        NULL, NULL);
  std::string strText;
  strText = pElementText;
  delete[] pElementText;
  return strText;
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

extern "C" PKGEXTERN Request_t RequestCreateNew()
{
    CppRest *cppRest=new CppRest();
    return cppRest;
}

extern "C" PKGEXTERN void RequestFree(Request_t rq)
{
    if(rq)
        delete static_cast<CppRest*>(rq);
}

extern "C" PKGEXTERN char *SendRequest(unsigned method,Request_t rq)
{
    return nullptr;
}

extern "C" PKGEXTERN void SetUserAgent(const char *ua,Request_t rq)
{
    if(rq==nullptr)
        return;
    CppRest *cppRest=static_cast<CppRest*>(rq);
    std::string sua=ua;
    std::wstring wua=MultiByteToUnicode(sua,CP_ACP);
    cppRest->SetUserAgent(wua);
}


static char *PackageRuntimeStandardRequestW(const wchar_t *ua,
    const wchar_t *host,
    unsigned method,
    const wchar_t *url,
    size_t *bufferSize,
    bool useSSL=false)
{
    DWORD dwStatusCode = 0;
    DWORD dwLastStatus = 0;
    DWORD dwSize=sizeof(DWORD);
    DWORD m_dwSize;
    BOOL bResults = FALSE;
    BOOL bDone=FALSE;
    CppRest::ApiResult result=CppRest::CPPREST_API_SERVERUNREACHABLE;
    DWORD dwProxyAuthScheme=0;
    HINTERNET hSession = nullptr,
    hConnect = nullptr,
    hRequest = nullptr;
    LPSTR pszOutBuffer=nullptr;
    DWORD dwDownloaded=0;
    wchar_t uaStr[512]=L"Charlie/1.0\0";
    if(ua)
    {
        memset(uaStr,0,512);
        wcsncpy(uaStr,ua,511);
    }

    hSession = WinHttpOpen(uaStr,
                           WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                           WINHTTP_NO_PROXY_NAME,
                           WINHTTP_NO_PROXY_BYPASS, 0);

    // Specify an HTTP server
    INTERNET_PORT nPort = (useSSL) ? INTERNET_DEFAULT_HTTPS_PORT : INTERNET_DEFAULT_HTTP_PORT;
    if (hSession)
        hConnect = WinHttpConnect(hSession,host,
                                  nPort, 0);
      wprintf(L"Host:%ls\n",host);
    // Create an HTTP Request handle.
    unsigned md=0;
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect,GetMethodString(method),
                                      url,
                                      NULL,
                                      WINHTTP_NO_REFERER,
                                      WINHTTP_DEFAULT_ACCEPT_TYPES,
                                      (useSSL)?WINHTTP_FLAG_SECURE:0);
    wprintf(L"Method:%ls\n",GetMethodString(method));
    wprintf(L"URL:%ls\n",url);
    //std::wcout<<
    if(hRequest==nullptr)
        bDone=TRUE;
    //FIXME This Function Memory Leek.
    while (!bDone){
        if (hRequest)
            bResults = WinHttpSendRequest(hRequest,
                WINHTTP_NO_ADDITIONAL_HEADERS,
                0, WINHTTP_NO_REQUEST_DATA, 0,
                0, 0);
        if (bResults)
            bResults = WinHttpReceiveResponse(hRequest, NULL);
        if (bResults){
            do{
            // Verify available data.
                m_dwSize = 0;
                if (!WinHttpQueryDataAvailable(hRequest, &m_dwSize))
                    printf("Error %u in WinHttpQueryDataAvailable.\n",GetLastError());
                    // Allocate space for the buffer.
                pszOutBuffer =(LPSTR)malloc(sizeof(char)*m_dwSize+1);
                // Read the Data.
                ZeroMemory(pszOutBuffer, m_dwSize+1);
                if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,m_dwSize, &dwDownloaded)){
                //printf("Error %u in WinHttpReadData.\n", GetLastError());
                    free(pszOutBuffer);
                    pszOutBuffer=nullptr;
                }else{
                    printf("Page:%s\n",pszOutBuffer);
                    printf("BufferSize:%d\n",m_dwSize);
                    *bufferSize=m_dwSize;
                }
            }while (m_dwSize > 0);
        }
        if (bResults){
            dwSize = sizeof(dwStatusCode);
            bResults = WinHttpQueryHeaders(hRequest,
                WINHTTP_QUERY_STATUS_CODE |
                WINHTTP_QUERY_FLAG_NUMBER,
                NULL,
                &dwStatusCode,
                &dwSize,
                NULL);
        }
        if (bResults){
            switch (dwStatusCode){
                case 200:
                bDone = TRUE;
                result = CppRest::ApiResult::CPPREST_API_200;
                break;
                case 401:
                bDone = TRUE;
                result = CppRest::ApiResult::CPPREST_API_401;
                break;
                case 403:
                result = CppRest::ApiResult::CPPREST_API_403;
                bDone = TRUE;
                break;
                case 407:
                bDone = TRUE;
                break;
                default:
                bDone = TRUE;
            }
        }
        dwLastStatus = dwStatusCode;
        if (!bResults){
            bDone = TRUE;
        }
    }

    // Report any errors.
    if (!bResults)
    {
        //DWORD dwLastError = GetLastError();
        //printf("Error %d has occurred.\n", dwLastError);
        result = CppRest::ApiResult::CPPREST_API_SERVERUNREACHABLE;
    }
    // Report errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    return pszOutBuffer;
}


extern "C" PKGEXTERN char *PackageRuntimeStandardRequest(const char *ua,
    const char *host,
    unsigned method,
    const char *url,
    size_t *bufferSize,
    bool useSSL)
{
    char *p=nullptr;
    if(host==nullptr)
        return nullptr;
    std::string sua;
    std::string shost=host;
    std::string surl;
    if(ua==nullptr)
        sua="Charlie/1.0";
    std::wstring wua=MultiByteToUnicode(sua,CP_ACP);
    std::wstring whost=MultiByteToUnicode(shost,CP_ACP);
    if(url==nullptr){
        return PackageRuntimeStandardRequestW(wua.c_str(),whost.c_str(),method,nullptr,bufferSize,useSSL);
    }
    surl=url;
    std::wstring wurl=MultiByteToUnicode(surl,CP_ACP);
    return PackageRuntimeStandardRequestW(wua.c_str(),whost.c_str(),method,wurl.c_str(),bufferSize,useSSL);
}

extern "C" PKGEXTERN void RequestBufferFree(void *p)
{
    if(p)
      free(p);
}
