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

Base64 dwFlags CRYPT_STRING_BASE64

*/

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
    std::wstring realpath=urlsu.rawpath+L"info/refs?service=git-upload-pack";
    return true;
}


bool CloneStep::RequestPOST(URLStruct &us)
{
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
