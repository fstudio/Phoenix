/*********************************************************************************************************
*   Phoenix Encoding Convert C++ Cross Platfrom
*   Note: CodeConvert.hpp
*   Date: 2015.01.25
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_CODECVT_HPP
#define PHOENIX_CODECVT_HPP
#if defined(_MSC_VER) && _MSC_VER >= 1800
#define CODECVT_ENABLE 1
#elif defined(__cplusplus) && __cplusplus >= 201103L
#define CODECVT_ENABLE 1
#else
#define CODECVT_ENABLE 0
#endif

#if CODECVT_ENABLE
#include <string>
#include <locale>
#if defined(_LIBCPP_VERSION) || defined(_MSC_VER)
////GCC 5.0 add codecvt
#include <codecvt>
#elif defined(__GNUC__) && __GNUC__ >= 5
#include <codecvt>
#else
#include <bits/codecvt.h>
#endif
#else
#error "Not Enable codecvt template "
#endif


template <class T>
class CodeCvtResolve{
public:
    typedef typename T::value_type Character;
};
bool WideStringToString(const std::wstring& src,std::string &str);
bool StringToWideString( const std::string& src,std::wstring &wstr);
bool WCharStringToUTF8String(const std::wstring &wstr,std::string &u8sr);
bool UTF8StringToWCharString(const std::string &u8str,st::wstring &wstr);

#endif