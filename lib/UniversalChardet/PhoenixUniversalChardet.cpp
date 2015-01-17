/*********************************************************************************************************
* PhoenixUniversalChardet.cpp
* Thanks Mozilla Foundation
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>
#include <string>
#include <cstdlib>
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
     int nLen = (int)str.length();
     wstr.resize(nLen,L' ');
     int nResult = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),nLen,(LPWSTR)wstr.c_str(),nLen);
     if (nResult == 0)
     {
         return false;
     }
     return true;
 }
 static bool WideStringToString(const std::wstring &wstr,std::string &str)
 {
     int nLen = (int)wstr.length();
     str.resize(nLen,' ');
     int nResult = WideCharToMultiByte(CP_ACP,0,static_cast<LPCWSTR>(wstr.c_str()),nLen,const_cast<LPSTR>(str.c_str()),nLen,NULL,NULL);
     if (nResult == 0)
     {
         return false;
     }
     return true;
 }
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
    strcpy_s(charset,Phdet->m_charset.c_str(),Phdet->m_charset)
    delete Phdet;
    return charset;
}
