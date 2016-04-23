/*********************************************************************************************************
* PhoenixUniversalChardet.cpp
* Thanks Mozilla Foundation
* @2014.08
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <wchar.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <UniversalChardet/UniversalChardet.h>
#include "base/nscore.h"
#include "base/nsUniversalDetector.h"

#ifdef _WIN32
class WideCharGet{
private:
    wchar_t *wstr;
public:
    WideCharGet(const char *str):wstr(nullptr)
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
    ~WideCharGet()
    {
        if(wstr)
            delete[] wstr;
    }
};

static bool StringToWideString(const std::string &str,std::wstring &wstr)
{
    int  len = 0;
    len = str.size();
    int  unicodeLen = ::MultiByteToWideChar(CP_ACP,
        0,
        str.c_str(),
        -1,
        NULL,
        0 );
    if(unicodeLen<=0)
        return false;
    wchar_t *  pUnicode;
    pUnicode = new  wchar_t[unicodeLen+1];
    memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));
    ::MultiByteToWideChar(CP_ACP,
        0,
        str.c_str(),
        -1,
        (LPWSTR)pUnicode,
        unicodeLen);
    wstr=pUnicode;
    delete  pUnicode;
    return true;
 }
static bool WideStringToString(const std::wstring &wstr,std::string &str)
{
    char*     pElementText;
    int    iTextLen;
    // wide char to multi char
    if(wstr.size()<=0)
        return false;
    iTextLen = WideCharToMultiByte( CP_ACP,
        0,
        wstr.c_str(),
        -1,
        NULL,
        0,
        NULL,
        NULL);
    pElementText = new char[iTextLen + 1];
    memset(pElementText, 0, sizeof(char)*(iTextLen+1));
    ::WideCharToMultiByte( CP_ACP,
        0,
        wstr.c_str(),
        -1,
        pElementText,
        iTextLen,
        NULL,
        NULL);
    str= pElementText;
    delete[] pElementText;
    return true;
}
////WinAPI Done
#else
class WideCharGet{
private:
    wchar_t *wstr;
public:
    WideCharGet(const char *str):wstr(nullptr)
    {
        if(str==nullptr)
            return ;
        const char* _Source = str;
        size_t _Dsize =strlen(str) + 1;
        wchar_t *_Dest = new wchar_t[_Dsize];
        wmemset(_Dest, 0, _Dsize);
        mbstowcs(_Dest,_Source,_Dsize);
        wstr= _Dest;
    }
    const wchar_t *Get()
    {
        if(!wstr)
            return nullptr;
        return const_cast<const wchar_t *>(wstr);
    }
    ~WideCharGet()
    {
        if(wstr)
            delete[] wstr;
    }
};
static bool StringToWideString(const std::string &str,std::wstring &wstr)
{
    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    wstr= _Dest;
    delete []_Dest;
    return true;
}
static bool WideStringToString(const std::wstring &wstr,std::string &str)
{
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2*ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    str = _Dest;
    delete []_Dest;
    return false;
}
/////Other System Done
#endif
//FIXME : This can check UTF-16 LE /BE or UTF-8 ,but ANSI-Based CodePages to be identified
class PhoenixUniversalDetector : public nsUniversalDetector
{
protected:
    string m_charset;

public:
    PhoenixUniversalDetector()
    : nsUniversalDetector(NS_FILTER_ALL)
    {
        m_charset = "ascii/unknown";
    }

    virtual ~PhoenixUniversalDetector()
    {}

    virtual void Report(const char* charset)
    {
        m_charset = charset;
    }

    virtual void Reset()
    {
        nsUniversalDetector::Reset();
        m_charset = "";
    }

    std::string GetCharset()
    {
        return m_charset;
    }
};


UniversalChardet::UniversalChardet(std::string data):status(false),m_charset("unknown"),wcharset(L"unknown")
{
    ///
    if(date.empty())
        return ;
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),date.length())!=NS_OK)
    {
        delete Phdet;
        return ;
    }
    Phdet->DataEnd();
    this->m_charset=Phdet->GetCharset();
    delete Phdet;
    StringToWideString(m_charset,wcharset)
    this->status=true;
}

UniversalChardet::~UniversalChardet()
{
    ///
}

std::string UniversalChardet::GetCharset()
{
    return this->m_charset;
}

std::wstring UniversalChardet::GetCharsetW()
{
    return this->wcharset;
}

static int GetCharsetCodePageFormChar(const char *p)
{
    if(strlen(p)<3)
        return -1;
    switch(p[0])
    {
        case 'U':
        return 65001;//Non BOM default.UTF-8
        case 'A':
        break;
        case 'B':
        break;
        case 'G':
        ///GBK GB2312 and ...
        break;
    }
    return 0;
}
////ANSI
int UniversalChardetFromFilePath(std::string filePath,bool &mark)
{
    FILE *fp=nullptr;
    if(fopen_s(&fp,filePath.c_str(),"r")!=0)
        return -1;
    char buffer[65536]={0};
    if(fread_s(buffer,1,65536,65536,fp)<0)
    {
        fclose(fp);
        return -2;
    }
    fclose(fp);
    if(buffer[0]==0xEF&&buffer[1]==0xBB&&buffer[2]==0xBF)
    {
        mark=true;
        return 65001;
    }
    if(buffer[0]==0xEF&&buffer[1]==0xFE)
        return 1200;
    if(buffer[0]==0xFF&&buffer[1]==0xFE)
        return 1201;
    static char charset[256]={0};
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),data.length())!=NS_OK)
    {
        delete Phdet;
        return -3;
    }
    Phdet->DataEnd();
    strcpy_s(charset,256,Phdet->m_charset.c_str());
    delete Phdet;
    return GetCharsetCodePageFormChar(p);
}
//WideChar
int UniversalChardetFromFilePath(std::wstring filePath,bool &mark)
{
    FILE *fp=nullptr;
    if(wfopen_s(&fp,filePath.c_str(),L"r")!=0)
        return -1;
    char buffer[65536]={0};
    if(fread_s(buffer,65536,1,65536,fp)<0)
    {
        fclose(fp);
        return -2;
    }
    fclose(fp);
    if(buffer[0]==0xEF&&buffer[1]==0xBB&&buffer[2]==0xBF)
    {
        mark=true;
        return 65001;
    }
    if(buffer[0]==0xEF&&buffer[1]==0xFE)
        return 1200;
    if(buffer[0]==0xFF&&buffer[1]==0xFE)
        return 1201;
    static char charset[256]={0};
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),data.length())!=NS_OK)
    {
        delete Phdet;
        return -3;
    }
    Phdet->DataEnd();
    strcpy_s(charset,256,Phdet->m_charset.c_str());
    delete Phdet;
    return GetCharsetCodePageFormChar(p);
}



extern "C" const char* UniversalGetCharSet(const char *text,size_t len)
{
    static char charset[256]={0};
        if(data.empty())
        return ;
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),data.length())!=NS_OK)
    {
        delete Phdet;
        return nullptr;
    }
    Phdet->DataEnd();
    strcpy_s(charset,256,Phdet->m_charset.c_str());
    delete Phdet;
    return charset;
}

extern "C" const wchar_t*  UniversalGetCharSetW(const char *text,size_t len)
{
    static wchar_t charset[256]={0};
    if(data.empty())
        return ;
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),data.length())!=NS_OK)
    {
        delete Phdet;
        return nullptr;
    }
    Phdet->DataEnd();
    //strcpy_s(charset,Phdet->m_charset.c_str(),Phdet->m_charset)
    std::wstring s;
    StringToWideString(Phdet->m_charset,s);
    wcscpy_s(charset,s.c_str(),256,Phdet->m_charset.c_str())
    delete Phdet;
    return charset;
}
