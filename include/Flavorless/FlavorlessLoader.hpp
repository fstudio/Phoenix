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
#include <sys/stat.h>

#ifdef _WIN32
#include <Windows.h>
#define fread fread_s
#endif
// GCC 5.0 support and clang+libcxx support MSVC 11 or later support


inline FILE *Open(const char *file)
{
    FILE *fp;
#ifdef _MSC_VER
    if(fopen_s(&fp,file,"rb")!=0||!fp)
        return nullptr;
#else
    if((fp=fopen(file,"rb"))==NULL)
        return nullptr;
#endif
    return fp;
}

inline FILE *Open(const wchar_t *file)
{
    FILE *fp;
#ifdef _WIN32
    if(_wfopen_s(&fp,file,L"rb")!=0)
        return nullptr;
#else
    std::wstring wstr=file;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string u8file = conv.to_bytes(wstr);
    if((fp=fopen(u8file.c_str(),"rb"))==nullptr)
        return nullptr;
#endif
    return fp;
}

///Warning this detect encoding: file must hava bom ,or your can user universalchardet
inline FlavorTP CharDet(FILE *fp)
{
    FlavorTP tp;
    char buffer[4]={0};
    if(fread(buffer,4,14,fp)==0)
    {
        return FlavorTP::FILETYPE_FAILED;
    }
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
////stat add wchar_t support
#ifdef _WIN32
#if defined(_MSC_VER) && (_MSC_VER > 1310)
static int stat(const wchar_t *path, struct _stat64i32 *buffer) {
    return _wstat(path, buffer);
}
#else
static int stat(const wchar_t *path, struct _stat *buffer) {
    return _wstat(path, buffer);
}
#endif
#else
static int stat(const wchar_t *path,struct stat *buffer)
{
    std::wstring wstr=path;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string u8file = conv.to_bytes(wstr);
    return stat(u8file.c_str(),buffer);
}
#endif

inline int64_t LastChangeTime(const char *filePtr)
{
#ifdef _WIN32
#if defined(_MSC_VER) && (_MSC_VER > 1310)
    struct _stat64i32 statusFile;
#else
    struct _stat statusFile;
#endif
#else
    struct stat statusFile;
#endif
    if (stat(filePtr, &statusFile) != -1)
        return statusFile.st_mtime;
    return 0;
}

inline int64_t LastChangeTime(const wchar_t *filePtr)
{
#ifdef _WIN32
#if defined(_MSC_VER) && (_MSC_VER > 1310)
    struct _stat64i32 statusFile;
#else
    struct _stat statusFile;
#endif
#else
    struct stat statusFile;
#endif
    if (stat(filePtr, &statusFile) != -1)
        return statusFile.st_mtime;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// + FlavorNizProcess Prase IniFile
// + inline wchar_t///
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline bool FlavorNizProcess(FILE *fp,FlavorTP tp,InitializeStructure<wchar_t> &iniStructure)
{
    FLAVORASSERT(fp);
    switch(tp)
    {
        case FILETYPE_UTF8:
        break;
        case FILETYPE_UTF16LE:
        break;
        case FILETYPE_UTF16BE:
        break;
        case FILETYPE_ANSI:
        default:
        break;
    }
    return true;
}

inline bool FlavorNizProcess(FILE *fp,FlavorTP tp,InitializeStructure<char> &iniStructure)
{
    FLAVORASSERT(fp);
    return true;
}


#ifdef _WIN32
inline bool FlavorNizProcessNT(const wchar_t *file,FlavorTP tp,InitializeStructure<wchar_t> &iniStructure)
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    bool bRet=true;
    LPVOID mPtr=nullptr;
    LPVOID pBuffer;
    DWORD NumberOfBytesRead;
    hFile=CreateFileW(file,GENRIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    if(mSize>0x8000000)
    {
        CloseHandle(hFile);
        return false;
    }
    mPtr=malloc(sizeof(char)*mSize+1); ///Big Memory.
    memset(mPtr,0,sizeof(char)*mSize+1);
    ReadFile(hFile,mPtr,mSize,&NumberOfBytesRead,NULL);
    switch(tp)
    {
        case FILETYPE_UTF8:{
            auto u8Ptr=reinterpret_cast<char*>(mPtr);
        }
        break;
        case FILETYPE_UTF16LE:
        {
            auto wPtr=reinterpret_cast<wchar_t*>(mPtr);
            ///Not Convert
        }
        break;
        case FILETYPE_UTF16BE:
        break;
        case FILETYPE_ANSI:
        default:
        break;
    }

    ////The End
    if(mPtr)
        free(mPtr);
    CloseHandle(hFile);
    return bRet;
}

inline bool FlavorNizProcessNT(const char* file,FlavorTP tp,InitializeStructure<char> &iniStructure)
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    bool bRet=true;
    hFile=CreateFileA(file,GENRIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    if(mSize>0x8000000)
        goto Close;
Close:
    CloseHandle(hFile);
    return true;
}



#endif




template<class Character>
class FlavorlessLoader{
private:
    typedef std::basic_fstream<Character> Fstream;
    typedef std::basic_string<Character> String;
private:
    int64_t filetime;
    int64_t filesize;
    String file;
public:
    FlavorlessLoader(){}
    bool Loader(const Character *filePtr,InitializeStructure<Character> &iniStructure)
    {
        if(!filePtr)
            return false;
        file=filePtr;
        FILE *fp=Open(filePtr);
        if(!fp)
            return false;
        this->filetime=LastChangeTime(filePtr);
        auto tp=CharDet(fp);
        auto bRet=FlavorNizProcess(fp,tp,iniStructure);
        fclose(fp);
        return true;
    }
    bool IsChanged(const Character *filePtr=nullptr)
    {
        if(LastChangeTime(filePtr?filePtr:file.c_str())==filetime) ///Not Changed
            return false;
        return true;
    }
    FlavorTP Detect(const Character *filePtr)
    {
        FILE *fp=Open(filePtr);
        if(!fp)
            return FlavorTP::FILETYPE_FAILED;
        auto i=CharDet(fp);
        fclose(fp);
        return i;
    }
};

#endif
