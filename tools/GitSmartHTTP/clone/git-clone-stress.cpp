/*
*/
//#include <Windows.h>
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
//#include <winhttp.h>
//Base64 Encoding
#include "WinHttpClient.h"
#include <wincrypt.h>
#include <Shlwapi.h>
#include <stdint.h>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>
#include "GetOptInc.h"


struct URLStruct{
    std::wstring host;
    std::wstring rawpath;
    bool isSSL;
    int port;
};

#define USER_AGENT L"git/2.5.0.Simulator.0"

int DefaultPort(const wchar_t * scheme);
bool URLParse(const wchar_t* uri,
    std::wstring& scheme,
    std::wstring& hostname,
    int &port,
    std::wstring& path);

class CharGet{
private:
   char *cPtr;
   static char *TranslateEncoding(const wchar_t *wstr){
       char *pElementText;
       int iTextLen=WideCharToMultiByte(CP_UTF8, 0, wstr.c, -1, NULL, 0, NULL, NULL);
       pElementText=new char[iTextLen+1];
       memset((void*)pElementText,0,sizeof(char)*(iTextLen+1));
       auto Ret=::WideCharToMultiByte(CP_UTF8, 0, wstr, -1, pElementText, iTextLen,NULL, NULL);
       if(Ret=0){
           delete[] pElementText;
           return nullptr;
       }
       return pElementText;
   }
public:
   CharGet(std::wstring &wstr){
       cPtr=TranslateEncoding(wstr.c_str());
   }
   CharGet(const wchar_t *wstr){
       cPtr=TranslateEncoding(wstr);
   }
   ~CharGet(){
       if(cPtr){
           delete[] cPtr;
       }
   }
   char* get() const{
       return this->cPtr;
   }
};


class BBuffer{
private:
    BYTE *Ptr;
public:
    BBuffer(unsigned size)
    {
        if(size<UINT32_MAX/4)///1GB small
            Ptr=(BYTE*)malloc(sizeof(BYTE)*size);
        else
            Ptr=nullptr;
    }
    ~BBuffer(){
        if(Ptr)
            free(Ptr);
    }
    BYTE* get(){
        return this->Ptr;
    }
};

class Console{
private:
   HANDLE hConsole;
public:
   Console():hConsole(nullptr){
       hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
   }
   ~Console(){
       if(hConsole)
       {
           CloseHandle(hConsole);
       }
   }
   HANDLE get(){
       return this->hConsole;
   }
};
////When Failed Print Red word
int PrintError(const wchar_t *format,...)
{
    int ret;
    static Console hCon;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hCon.get(), &bInfo);
    SetConsoleTextAttribute(hCon.get(),FOREGROUND_RED|FOREGROUND_INTENSITY);
    va_list ap;
    va_start(ap, format);
    ret=vwprintf_s(format,ap);
    va_end(ap);
    SetConsoleTextAttribute(hCon.get(),bInfo.wAttributes);
    return ret;
}

enum PrintColor{
    NO_COLOR=0
};

int Print(WORD color,const wchar_t *format,...){
    int ret;
    static Console hCon;
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo(hCon.get(), &bInfo);
    SetConsoleTextAttribute(hCon.get(),color);
    va_list ap;
    va_start(ap, format);
    ret=vwprintf_s(format,ap);
    va_end(ap);
    SetConsoleTextAttribute(hCon.get(),bInfo.wAttributes);
    return 0;
}

static wchar_t recordfile[4096]={0};

int RecordError(const wchar_t *format,...)
{
    int ret;
    FILE *fp;
    if(_wfopen_s(&fp,recordfile,L"a+")!=0)
       return 0;
    va_list ap;
    va_start(ap, format);
    ret=vfwprintf_s(fp,format,ap);
    va_end(ap);
    fclose(fp);
    return ret;
}


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
BOOL WINAPI PasswordEncodingBase64(const wchar_t* name,const wchar_t* pwd,std::wstring &outtext)
{
    char buffer[512]={0};
    CharGet cname(name);
    CharGet cpwd(pwd);
    wchar_t receivebuf[1024]={0};
    sprintf_s(buffer,512,"%s:%s",cname.get(),cpwd.get());
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
001e# service=git-upload-pack
000000d16b608d3d4c01a5933342823a0cdfde90f8753301 HEADmulti_ack thin-pack side-band side-band-64k ofs-delta shallow no-progress include-tag multi_ack_detailed no-done symref=HEAD:refs/heads/master agent=git/1.9.1
00410d2661d52ca24946d3a6945424f71fd1c0f8dcb8 refs/heads/gh-pages
003f6b608d3d4c01a5933342823a0cdfde90f8753301 refs/heads/master
003be8ad4c2d0953b1cb3d7a01e27db7a20d51e85168 refs/tags/1.0
003d9e0f6cc8b1ff90c12bd301bfe05b58671fb474e4 refs/tags/1.0.2
003d6373e88d0680a7e22df40637346c55e33c467aff refs/tags/1.0.3
003ea98d1eb56a704f29cf7f8b7a74b4a5c53371d1f8 refs/tags/v1.0.4
0000

008awant adb4536c655707a637aa74aef0d899ef57b28a1d multi_ack_detailed no-done side-band-64k thin-pack ofs-delta agent=git/2.5.0.Simulator.0
0032want adb4536c655707a637aa74aef0d899ef57b28a1d
0032want adb4536c655707a637aa74aef0d899ef57b28a1d
00000009done

************************** */

BOOL WINAPI ResolveContent(const BYTE* raw,unsigned len,BYTE *buffer,unsigned *bufferSize)
{
    auto end=raw+len;
    auto begin=raw;
    BYTE line[2048]={0};
    unsigned ll=0;
    BYTE fline[41]={0};
    static std::stringstream sstr;
    while(begin++<end&&ll<2047)
    {
        if(*begin==0x0A)
        {
            if(ll>70&&memcmp(line,"0000",4)==0)
            {
                auto oid=const_cast<BYTE*>(line+8);
                memcpy(fline,oid,40);
                sstr<<"008awant "<<fline<<L" multi_ack_detailed no-done side-band-64k thin-pack ofs-delta agent=git/2.5.0.Simulator.0\n";
            }else if(ll>56){
                auto oid=const_cast<BYTE*>(line+4);
                memcpy(fline,oid,40);
                sstr<<"0032want "<<fline<<"\n";
            }else{
                /////Not do more
            }
            ll=0;
        }else{
            line[ll]=*begin;
            ll++;
        }
    }
    sstr<<"00000009done\n";
    memcmp(buffer,sstr.str().c_str(),sstr.str().size());
    *bufferSize=sstr.str().size();
    return TRUE;
}

class CloneStep{
private:
    /// Basic xXxxxxxxxxxxxxxxxx
    std::wstring base64Info;
    bool enableBase64;
    std::wstring murl;
    bool RequestGET();
    bool RequestPOST(URLStruct &us,BYTE* content,unsigned len);
public:
    CloneStep(std::wstring url):murl(url),enableBase64(false){}
    CloneStep(){}
    bool SetURL(const wchar_t *url){
        murl.assign(url);
        return true;
    }
    bool SetAuthInfo(std::wstring &binfo)
    {
        this->base64Info=binfo;
        this->enableBase64=this->base64Info.size()>10?true:false
        return this->enableBase64;
    }
    int Start();
};

bool CloneStep::RequestGET()
{
    ///
    ///std::wstring get_url=this->murl+L"info/refs?service=git-upload-pack";
    URLStruct urlAtom;
    std::wstring scheme;
    urlAtom.isSSL=false;
    if(!URLParse(this->murl.c_str(),scheme,urlAtom.host,urlAtom.port,urlAtom.rawpath))
    {
        wprintf(L"Failed to Parse URL: %s\n",this->murl.c_str());
        return false;
    }
    if(scheme.compare(L"https"))
        urlAtom.isSSL=true;
    std::wstring header=L"Accept-Encoding: gzip\r\nConnection: keep-alive\r\n";
    if(this->enableBase64){
        header+=L"Authorization: "+this->base64Info+L"\r\n";
    }
    std::wstring requestURL=murl+L"info/refs?service=git-upload-pack";
    WinHttpClient client(requestURL);
    std::wstring headers=L"Accept: */*\r\nAccept-Encoding: gzip\r\nPragma: no-cache\r\n";
    client.SetRequireValidSslCertificates(urlAtom.isSSL);
    client.SetAdditionalRequestHeaders(headers);
    client.SendHttpRequest();
    std::wstring httpResponseHeader=client.GetResponseHeader();
    auto raw=client.GetRawResponseContent();
    auto size=client.GetRawResponseContentLength();
    wprintf(L"Response Header:\n%s\n",httpResponseHeader.c_str());
    BBuffer buffer(size);
    unsigned bufferSize=0;
    if(ResolveContent(raw,size,buffer.get(),&bufferSize)){
        return this->RequestPOST(urlAtom,buffer.get(),bufferSize);
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

bool CloneStep::RequestPOST(URLStruct &us,BYTE* content,unsigned len)
{
    /*
    Content-Type: application/x-git-upload-pack-request
    Accept: application/x-git-upload-pack-result
    */
    std::wstring requestURL=this->murl+L"/git-upload-pack";
    WinHttpClient client(requestURL,ProgressProc);
    ////When POST not set gzip
    std::wstring headers=L"Content-Type: application/x-git-upload-pack-request\r\nAccept: application/x-git-upload-pack-result\r\n";
    if(this->enableBase64){
        header+=L"Authorization: "+this->base64Info+L"\r\n";
    }
    headers+=L"Content-Length: ";
    wchar_t szSize[50] = L"";
    swprintf_s(szSize, L"%d", len);
    headers += szSize;
    client.SetRequireValidSslCertificates(us.isSSL);
    client.SetAdditionalRequestHeaders(headers);
    client.SendHttpRequest(L"POST");
    client.SetAdditionalDataToSend(content,len);
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
    wchar_t localeBuffer[80]={0};
    LCIDToLocaleName(lcid,localeBuffer,LOCALE_NAME_MAX_LENGTH,LOCALE_ALLOW_NEUTRAL_NAMES);
    _wsetlocale(LC_ALL,localeBuffer);
    GetTempPathW(MAX_PATH,recordfile);
    wcscat_s(recordfile,MAX_PATH,L"git-clone-stress.error.log");
    return true;
}

static bool SplitParentDir(const wchar_t *filePath)
{
    wchar_t drive[128]={0};
    wchar_t dir[4096]={0};
    wchar_t filename[256]={0};
    wchar_t ext[128]={0};
    if(_wsplitpath_s(filePath,drive,dir,filename,ext)!=0)
        return false;
    wprintf(L"Dir: %s\n",dir);
    return true;
}
// PathStripPath Get FileName
//git-clone-stress --input(-i) repo.list -e some@site.com -p password
int wmain(int argc,wchar_t **argv)
{
    ///Initialize Environment ,support wchar_t output
    //PrintError(L"Argv[0]:%s\nError Report\n",argv[0]);
    std::wstring email;
    std::wstring password;
    std::wstring base64text;
    Initialize();
    int ch;
    const wchar_t *short_opts=L"hvi:e:l:p";
    const option option_long_opt[]={
     {L"help",no_argument,NULL,'h'},
     {L"version",no_argument,NULL,'v'},
     {L"input",required_argument ,NULL,'i'},
     {L"email",required_argument ,NULL,'e'},
     {L"log",required_argument,NULL,'l'},
     {L"password",required_argument ,NULL,'p'},
     {0,0,0,0}
    };
    while((ch=getopt_long(argc,argv,short_opts,option_long_opt,NULL))!=-1)
    {
        ///
        switch(ch){
            case 'h':
            //print usage and exit
            break;
            case 'v':
            //print version
            break;
            case 'e':
            email=optarg
            break;
            case 'i':
            wprintf(L"Input: %s\n",optarg);
            break;
            case 'l':
            {
                wchar_t mLog[4096]={0};
                wcscpy_s(mLog,optarg);
                PathRemoveFileSpec(mLog);
                if(!PathFileExists(mLog)){
                    PrintError(L"Dir %s is not exists,your should changed your log file dir\n",mLog);
                    return 1;
                }
                ///Check  Folder  exists
            }
            break;
            case 'p':
            password=optarg;
            break;
            default:
            break;
        }
    }
    CloneStep cloneStep;
    if(!(email.empty()||password.empty()))
    {
        if(email.size()+password.size()<340){
            if(PasswordEncodingBase64(email.c_str(),password.c_str(),base64text))
            {
                base64text=L"Basic "+base64text;
                cloneStep.SetAuthInfo(base64text);
            }
        }
    }
    

    return 0;
}
