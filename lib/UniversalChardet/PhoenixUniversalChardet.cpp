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
#include <UniversalChardet/UniversalChardet.h>
#include "base/nscore.h"
#include "base/nsUniversalDetector.h"


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


UniversalChardet::UniversalChardet(std::string data):status(false),m_charset("unknown")
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
    this->status=true;
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
