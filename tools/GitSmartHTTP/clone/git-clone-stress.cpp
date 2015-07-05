/*
*/
#include <Windows.h>
#include <string>
#include <winhttp.h>
//Base64 Encoding
#include <wincrypt.h>
#include <stdint.h>

#pragma comment(lib,"crypt32.lib")

struct URLStruct{
    std::wstring host;
    std::wstring rawpath;
    bool isSSL;
    uint32_t port;
};

#define USER_AGENT L"git/2.0"

/*
BOOL WINAPI CryptBinaryToString(
  _In_      const BYTE   *pbBinary,
  _In_            DWORD  cbBinary,
  _In_            DWORD  dwFlags,
  _Out_opt_       LPTSTR pszString,
  _Inout_         DWORD  *pcchString
);


BOOL WINAPI CryptStringToBinary(
  _In_    LPCTSTR pszString,
  _In_    DWORD   cchString,
  _In_    DWORD   dwFlags,
  _In_    BYTE    *pbBinary,
  _Inout_ DWORD   *pcbBinary,
  _Out_   DWORD   *pdwSkip,
  _Out_   DWORD   *pdwFlags
);


Base64 dwFlags CRYPT_STRING_BASE64

*/

/// Name and pwd to UTF8
BOOL WINAPI PasswordEncodingBase64(const char* name,const char* pwd,std::wstring &outtext)
{
    char buffer[512]={0};
    wchar_t receivebuf[1024]={0};
    sprintf_s(buffer,512,"%s:%s",name,pwd);
    auto size=strlen(buffer);
    DWORD  pcchString;
    auto bRet=CryptBinaryToStringW(
        (const BYTE*)(buffer),
        size,
        CRYPT_STRING_BASE64,
        receivebuf,
        &pcchString);
    if(bRet){
        outtext=receivebuf;
    }
    return bRet;
}

int DefaultPort(const wchar_t * scheme);
bool URLParse(const wchar_t* uri,
    std::wstring& scheme,
    std::wstring& hostname,
    int& port,
    std::wstring& path);

class CloneStep{
private:
    /// Basic xXxxxxxxxxxxxxxxxx
    std::wstring base64Info;
    std::wstring murl;
    bool RequestGET();
    bool RequestPOST(URLStruct &us);
public:
    CloneStep(std::wstring url):murl(url){}
    CloneStep(){}
    bool SetURL(const wchar_t *url){
        murl.assign(url);
        return true;
    }
    int Start();
};

/*

typedef int(*ReceiveResponeCallBack)(char *p,size_t buffer,void* t);

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

*/

static BOOL RequestFlush()
{
    return TRUE;
}

/*
// Specify an HTTP server.
if (hSession)
    hConnect = WinHttpConnect( hSession, L"www.example.com",
                               INTERNET_DEFAULT_HTTP_PORT, 0);

// Create an HTTP request handle.
if (hConnect)
    hRequest = WinHttpOpenRequest( hConnect, L"GET", L"/path/resource.html",
                                   NULL, WINHTTP_NO_REFERER,
                                   WINHTTP_DEFAULT_ACCEPT_TYPES,
                                   WINHTTP_FLAG_SECURE);

// Send a request.
if (hRequest)
    bResults = WinHttpSendRequest( hRequest,
                                   WINHTTP_NO_ADDITIONAL_HEADERS,
                                   0, WINHTTP_NO_REQUEST_DATA, 0,
                                   0, 0);
*/
bool CloneStep::RequestGET()
{
    ///
    ///std::wstring get_url=this->murl+L"info/refs?service=git-upload-pack";
    URLStruct urlsu;
    std::wstring scheme;
    urlsu.isSSL=false;
    if(!URLParse(this->murl.c_str(),scheme,urlsu.host,urlsu.port,urlsu.rawpath))
    {
        wprintf(L"Failed to Parse URL: %s\n",this->murl.c_str());
        return false;
    }
    if(scheme==L"https")
        urlsu.isSSL==true;
    std::wstring header=L"Accept-Encoding: gzip\r\nConnection: keep-alive\r\n";
    std::wstring realpath=urlsu.rawpath+L"info/refs?service=git-upload-pack";
    return true;
}


bool CloneStep::RequestPOST(URLStruct &us)
{
    /*
    Content-Type: application/x-git-upload-pack-request
    Accept: application/x-git-upload-pack-result
    */
    return true;
}

int CloneStep::Start()
{
    //
    return 0;
}

int wmain(int argc,wchar_t **argv)
{
    return 0;
}
