/*********************************************************************************************************
* FlavorlessInternal.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_INTERNAL_H
#define FLAVORLESS_INTERNAL_H
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>

#ifdef _WIN32

#ifndef FORCE_USE_WCHAR
#define FORCE_USE_WCHAR 1
#endif

#else

#ifndef FORCE_USE_WCHAR
#define FORCE_USE_WCHAR 0
#endif

#endif

#if FORCE_USE_WCHAR
#define Char wchar_t
#else
#define Char char
#endif

#ifdef _DEBUG
#ifndef assert
#include <cassert>
#endif
#define FLAVORASSERT(x) assert(x)
#else
#define FLAVORASSERT(x)
#endif

enum FlavorError{
    FLAVOR_OK=0,
    FLAVOR_UPDATE=1, ///some value was changed
    FLAVOR_INSERTED=2,////a new value
    ////
    FLAVOR_FAILED=-1,
    FLAVOR_NORMAL=-2,
    FLAVOR_FILE=-3
};

typedef enum Flavor_FileTYPE_Flags
{
    FILETYPE_ANSI=0,
    FILETYPE_UTF8=1,
    FILETYPE_UTF16LE=2,
    FILETYPE_UTF16BE=3,
    FILETYPE_UNKNWON=4,
    FILETYPE_FAILED=5
}FlavorTP;


#define NEWLINE_CRLF "\r\n"
#define NEWLINE_CRLFW L"\r\n"
#define NEWLINE_LF "\n"
#define NEWLINE_LFW  L"\n"

template <class Character>
class InitializeStructure{
public:
    InitializeStructure(){
        ///
    }
    typedef std::basic_string<Character> String;
    struct Section{
        const Character *name;
        std::unordered_map<String,String> nv;
        std::unordered_map<int,String> comments;
        int nOrder;
    };
    std::list<Section> listSection;
};



#endif
