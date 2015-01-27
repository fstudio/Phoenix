/*********************************************************************************************************
*   Phoneix Ini  Features
*   Note: IniResolve.cpp
*   Data: 2015.01.22
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include "IniResolve.hpp"
#ifndef _WIN32
#error "Only Support Windows"
#endif
#include <Windows.h>
///MultiByteToUnicode
#include <Encoding/Encode.h>

static const char bom_utf8[] = {0xEF,0xBB,0xBF};

static inline void IniResolveWriteMarker(HANDLE hFile,IniResolveFileEncoding encoding)
{
    DWORD dwBytesWritten;
    WCHAR bom;
    switch (encoding)
    {
    case INIRESOLVE_ENCODING_ANSI:
    case INIRESOLVE_ENCODING_UTF8_WITHOUTBOM
      break;
    case INIRESOLVE_ENCODING_UTF8_WITHBOM:
        WriteFile(hFile, bom_utf8, sizeof(bom_utf8), &dwBytesWritten, NULL);
        break;
    case INIRESOLVE_ENCODING_UTF16LE:
        bom = 0xFEFF;
        WriteFile(hFile, &bom, sizeof(bom), &dwBytesWritten, NULL);
        break;
    case INIRESOLVE_ENCODING_UTF16BE:
        bom = 0xFFFE;
        WriteFile(hFile, &bom, sizeof(bom), &dwBytesWritten, NULL);
        break;
    }
}

static bool  IniResolveFileAccess(const std::wstring &path)
{
    WIN32_FILE_ATTRIBUTE_DATA attr_data;
    if(GetFileAttributesExW(path.c_str(),GetFileExInfoStandard,&attr_data)!=TRUE)
        return false;
    if(attr_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        ///This directory
        return false;
    }
    if ( (attr_data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) && 2 ) {
        return false;
    }
    return true;
}

static bool IniResolveFileAccess(const std::string &path)
{
    WIN32_FILE_ATTRIBUTE_DATA attr_data;
    if(GetFileAttributesExA(path.c_str(),GetFileExInfoStandard,&attr_data)!=TRUE)
        return false;
    if(attr_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return false;
    }
    if ( (attr_data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) && 2 ) {
        return false;
    }
    return false;
}

static wchar_t* IniResolveReaderW(/*_In_*/HANDLE hFile,uint64_t mSize)
{
    auto p=(wchar_t *)malloc(mSize/2+1);
    DWORD dw;
    if(!ReadFile(static_cast<HANDLE>(hFile),p,mSize,&dw,nullptr))
    {
        free(p);
        return nullptr;
    }
    return p;
}

static char* IniResolveReaderA(HANDLE hFile,uint64_t mSize)
{
    auto p=(char *)malloc(mSize+1);
    DWORD dw;
    if(!ReadFile(static_cast<HANDLE>(hFile),p,mSize,&dw,nullptr))
    {
        free(p);
        return nullptr;
    }
    return p;
}

static void IniResolveMemoryFree(void *p)
{
    if(p)
        free(p);
}


////
bool IniResolveUnicode::Loader()
{
    if(m_iniFile.empty())
        return false;
    if(!IniResolveFileAccess(this->m_iniFile))
        return false;
    if(!this->CheckIniFileChardet())
        return false;
    HANDLE hFile=nullptr;
    return false;
}

bool IniResolveMultiByte::Loader()
{
    //
    if(m_iniFile.empty())
        return false;
    if(!IniResolveFileAccess(this->m_iniFile))
        return false;
    if(!this->CheckIniFileChardet())
        return false;
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    hFile=CreateFileW(rePath.c_str(),GENRIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    if(mSize>0x4000000)//64MB
    {
        ///
        CloseHandle(hFile);
        return false;
    }
    switch(this->codePage)
    {
        case 1200:
        break;
        case 1201:
        break;
        case 65001:
        default:
        break;
    }
    return false;
}




bool SmapleCfgResolveUnicode::Loader()
{
    if(this->cfgFile.empty())
        return false;
    return true;
}