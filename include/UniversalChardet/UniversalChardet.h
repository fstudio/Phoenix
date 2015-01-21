/*********************************************************************************************************
*   UniversalChardet.h
*   Thanks Mozilla Foundation
*   Note: Phoenix Universial Chardet Library
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2014 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_UNIVERSALCHARDET_H
#define PHOENIX_UNIVERSALCHARDET_H
#include <string>

#ifdef __cplusplus
namespace Character_{
#else
typedef struct Character{
#endif

enum Phoenix_Character_SET_{
    CharacterSET_ASCII=0,
    CharacterSET_UTF8=1,
    CharacterSET_UTF16LE=2,
    CharacterSET_UTF16BE=3
};
#ifdef __cplusplus
}
#else
}Character;
#endif

#ifdef __cplusplus
class UniversalChardet{
private:
    std::wstring wcharset;
    std::string m_charset;
    bool status;
public:
    UniversalChardet(std::string data);
    ~UniversalChardet();
    std::wstring GetCharsetW();
    std::string GetCharset();
    bool GetStatus(){return this->status;}
};

#endif

#ifdef __cplusplus
extern "C"{
#endif
const char* UniversalGetCharSet(const char *text,size_t len);
const wchar_t*  UniversalGetCharSetW(const char *text,size_t len);
#ifdef __cplusplus
}
#endif


#endif
