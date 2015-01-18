/*********************************************************************************************************
* PhoenixUniversalChardet.cpp
* Thanks Mozilla Foundation
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <UniversalChardet/UniversalChardet.h>
#include "base/nscore.h"
#include "base/nsUniversalDetector.h"

#ifdef _WIN32
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
    this->m_charset=Phdet->m_charset;
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


extern "C" const char* UniversalGetCharSet(const char *text,size_t len)
{
    static char charset[256]={0};
        if(date.empty())
        return ;
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),date.length())!=NS_OK)
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
    if(date.empty())
        return ;
    PhoenixUniversalDetector *Phdet=new PhoenixUniversalDetector();
    if(Phdet->HandleData(data.c_str(),date.length())!=NS_OK)
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