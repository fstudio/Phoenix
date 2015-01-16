/*********************************************************************************************************
* UniversalChardet.h
* Thanks Mozilla Foundation
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#ifndef PHOENIX_UNIVERSALCHARDET_H
#define PHOENIX_UNIVERSALCHARDET_H
#include <string>

#ifdef __cplusplus
class UniversalChardet{
private:
    std::wstring m_charset;
    bool status;
public:
    UniversalChardet(std::string data);
    ~UniversalChardet();
    std::wstring GetCharset();
    bool GetStatus(){return this->status;}
};
#endif

#ifdef __cplusplus
extern "C"{
#endif
const char* UniversalGetCharSet(const char *text,size_t len);

#ifdef __cplusplus
}
#endif


#endif
