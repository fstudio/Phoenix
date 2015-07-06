/*
*/
//#include <Windows.h>
#include <string>
//#include <winhttp.h>
//Base64 Encoding
#include <wincrypt.h>
#include <stdint.h>
#include <vector>
#include "WinHttpClient.h"

#pragma comment(lib,"crypt32.lib")

struct URLStruct{
    std::wstring host;
    std::wstring rawpath;
    bool isSSL;
    uint32_t port;
};

#define USER_AGENT L"git/2.5.0.Simulator.0"

int DefaultPort(const wchar_t * scheme);
bool URLParse(const wchar_t* uri,
    std::wstring& scheme,
    std::wstring& hostname,
    int& port,
    std::wstring& path);

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

 /*************
<NULL> is \x00
00dbadb4536c655707a637aa74aef0d899ef57b28a1d HEAD<NULL>multi_ack thin-pack side-band side-band-64k ofs-delta shallow no-progress include-tag multi_ack_detailed no-done symref=HEAD:refs/heads/master agent=git/1.9.5.msysgit.1
003fadb4536c655707a637aa74aef0d899ef57b28a1d refs/heads/master
0048adb4536c655707a637aa74aef0d899ef57b28a1d refs/remotes/origin/master
0000

008awant adb4536c655707a637aa74aef0d899ef57b28a1d multi_ack_detailed no-done side-band-64k thin-pack ofs-delta agent=git/2.5.0.Simulator.0
0032want adb4536c655707a637aa74aef0d899ef57b28a1d
0032want adb4536c655707a637aa74aef0d899ef57b28a1d
00000009done

************************** */
    
bool RefsLineParse(std::wstring &line,std::wstring &id)
{
    wchar_t buffer[5]={0};
    swprintf(buffer,4,L"%s",line.c_str());
    if(line.size>44){
        id=line.substr(4,40);   
    }
    return true;
}

BOOL WINAPI ResolveContent(std::wstring &raw,std::wstring &out)
{
    static std::wstringstream sstr;
    auto sz=raw.size();
    std::wstring line;
    std::wstring oid;
    std::vector<std::wstring> oidv;
    for(wchar_t &c:raw)
    {
        if(c=='\r')
        {
            if(RefsLineParse(line,oid))
            {
                oidv.push_back(oid);
            }
            line.clear();
        }
        line.append(c);
    }
    auto len=sizeof(L"multi_ack_detailed no-done side-band-64k thin-pack ofs-delta agent=git/2.5.0.Simulator.0")/sizeof(wchar_t);
    sstr<<L"008awant "<<<<oidv.at(0)<<L" multi_ack_detailed no-done side-band-64k thin-pack ofs-delta agent=git/2.5.0.Simulator.0";
    for(auto i=1;i<oidv.size();i++)
        {
            sstr<<L"0032want "<<oidv[i]<<L"\r\n";
        }
    sstr<<L"00000009done";
    return TRUE;
}

class CloneStep{
private:
    /// Basic xXxxxxxxxxxxxxxxxx
    std::wstring base64Info;
    std::wstring murl;
    bool RequestGET();
    bool RequestPOST(URLStruct &us,std::wstring &content);
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
    std::wstring header=L"Accept-Encoding: gzip\r\nConnection: keep-alive\r\n";
    std::wstring requestURL=murl+L"info/refs?service=git-upload-pack";
    WinHttpClient client(requestURL);
    std::wstring headers=L"Accept: */*\r\nAccept-Encoding: gzip\r\nPragma: no-cache\r\n";
    client.SetRequireValidSslCertificates(urlsu.isSSL);
    client.SetAdditionalRequestHeaders(headers);
    client.SendHttpRequest();
    std::wstring httpResponseHeader=client.GetReponseHeader();
    std::wstring httpResponseContent=client.GetReponseContent();
    wprintf(L"Response Header:\n%s\n",httpResponseHeader.c_str());
    wprintf(L"\n\nResponse Body:\n%s\n",httpResponseContent);
    std::wstring refs;
    if(ResolveContent(httpResponseContent,refs)){
        return this->RequestPOST(urlsu,refs);
    }
    wprintf(L"Faied Parser Response Content");
    return false;
}

/*
POST /user/proj.git/git-upload-pack HTTP/1.1
User-Agent: git/2.5.0.Simulator.0
Host: git.oschina.net
Accept-Encoding: gzip
Content-Type: application/x-git-upload-pack-request
Accept: application/x-git-upload-pack-result
Content-Length: 399
*/

bool ProgressProc(double progress)
{
    wprintf(L"Current Receive Data:%-.1f%%\r\n",progress);
    return true;
}

bool CloneStep::RequestPOST(URLStruct &us,std::wstring &content)
{
    /*
    Content-Type: application/x-git-upload-pack-request
    Accept: application/x-git-upload-pack-result
    */
    std::wstring requestURL=this->murl+L"/git-upload-pack";
    WinHttpClient client(requestURL,ProgressProc);
    std::wstring headers=L"Accept-Encoding: gzip\r\nContent-Type: application/x-git-upload-pack-request\r\nAccept: application/x-git-upload-pack-result\r\n";
    headers+=L"Content-Length: ";
    wchar_t szSize[50] = L"";
    swprintf_s(szSize, L"%d", content.size());
    headers += szSize;
    client.SetRequireValidSslCertificates(us.isSSL);
    client.SetAdditionalRequestHeaders(headers);
    client.SendHttpRequest(L"POST");
    
    wstring httpResponseHeader = client.GetResponseHeader();
    wstring httpResponseContent = client.GetResponseContent();
    return true;
}

int CloneStep::Start()
{
    //
    return 0;
}

bool Initialize()
{
    auto lcid=GetSystemDefaultLCID();
    wchar_t szBuf[0]={0};
    LCIDToLocaleName(lcid,szBuf,LOCALE_NAME_MAX_LENGTH,LOCALE_ALLOW_NEUTRAL_NAMES);
    _wsetlocale(LC_ALL,szBuf);
    return true;
}

int wmain(int argc,wchar_t **argv)
{
    return 0;
}
