/*********************************************************************************************************
* FlavorlessLoader.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_LOADER_HPP
#define FLAVORLESS_LOADER_HPP
#include "FlavorlessInternal.h"
#include <fstream>


/*

    file.open(filePtr,std::ios_base::in|std::ios_base::binary);
    if(file.good())
    {
        char szPtr[3]={0};
        file.read(szPtr,sizeof(char)*3);
        if((unsigned char)szPtr[0]==0xFF&&(unsigned char)szPtr[1]==0xFE)
            tp=FILETYPE_UTF16LE;
        else if((unsigned char)szPtr[0]==0xFE&&(unsigned char)szPtr[1]==0xFF)
            tp=FILETYPE_UTF16BE;
        else if((unsigned char)szPtr[0]==0xEF&&(unsigned char)szPtr[1]==0xBB&&(unsigned char)szPtr[2]==0xBF)
            tp=FILETYPE_UTF8;
        else{
#ifdef _WIN32
            tp=FILETYPE_ANSI;
#else
            tp=FILETYPE_UTF8;
#endif
        }
    }
    file.close();
*/

#ifdef _WIN32
#define fread fread_s
#define OPENFLAGS "rb"
#define OPENFLAGSW L"rb"
#else
#define OPENFLAGS "r"
#define OPENFLAGSW L"r"
#endif

#include <codecvt>


inline FlavorTP DetectFileEncoding(const char *filePtr)
{
    FILE *fp;
#ifdef _MSC_VER
    if(fopen_s(&fp,filePtr,OPENFLAGS)!=0||!fp)
        return FlavorTP::FILETYPE_FAILED;
#else
    if((fp=fopen(filePtr,OPENFLAGS))==NULL)
        return FlavorTP::FILETYPE_FAILED;
#endif
    FlavorTP tp;
    char buffer[4]={0};
    if(fread(buffer,4,14,fp)==0)
    {
        fclose(fp);
        return FlavorTP::FILETYPE_FAILED;
    }
    fclose(fp);
    if((unsigned char)buffer[0]==0xFF&&(unsigned char)buffer[1]==0xFE)
        tp=FILETYPE_UTF16LE;
    else if((unsigned char)buffer[0]==0xFE&&(unsigned char)buffer[1]==0xFF)
        tp=FILETYPE_UTF16BE;
    else if((unsigned char)buffer[0]==0xEF&&(unsigned char)buffer[1]==0xBB&&(unsigned char)buffer[2]==0xBF)
        tp=FILETYPE_UTF8;
    else
        tp=FILETYPE_UNKNWON;
    return tp;
}

inline FlavorTP DetectFileEncoding(const wchar_t *filePtr)
{
    FILE *fp;
#ifdef _WIN32
    if(_wfopen_s(&fp,filePtr,OPENFLAGSW)!=0)
        return FlavorTP::FILETYPE_FAILED;
#else
    std::wstring wstr=filePtr;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string u8str = conv.to_bytes(wstr);
    if((fp=fopen(u8str.c_str(),OPENFLAGS))==nullptr)
        return FlavorTP::FILETYPE_FAILED;
#endif
    FlavorTP tp;
    char buffer[4]={0};
    if(fread(buffer,4,14,fp)==0)
    {
        fclose(fp);
        return FlavorTP::FILETYPE_FAILED;
    }
    fclose(fp);
    if((unsigned char)buffer[0]==0xFF&&(unsigned char)buffer[1]==0xFE)
        tp=FILETYPE_UTF16LE;
    else if((unsigned char)buffer[0]==0xFE&&(unsigned char)buffer[1]==0xFF)
        tp=FILETYPE_UTF16BE;
    else if((unsigned char)buffer[0]==0xEF&&(unsigned char)buffer[1]==0xBB&&(unsigned char)buffer[2]==0xBF)
        tp=FILETYPE_UTF8;
    else
        tp=FILETYPE_UNKNWON;
    return tp;
}

template<class Character>
class FlavorlessLoader{
public:
    typedef std::basic_fstream<Character> Fstream;
    typedef std::basic_string<Character> String;
    FlavorlessLoader(){}
    bool Loader(const Character *filePtr)
    {
        return true;
    }
    FlavorTP Detect(const Character *filePtr)
    {
        return DetectFileEncoding(filePtr);
    }
};

#endif
