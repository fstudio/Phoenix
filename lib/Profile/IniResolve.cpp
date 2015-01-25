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

static bool IniResolveFileAccessA(const std::string &path)
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

template <typename Character>
bool IniResolveFileOpen(const Character filePath,Character *buffer,size_t bufferSize)
{
    if(filePath==nullptr||buffer==nullptr)
        return false;
    return false;
}

////
bool IniResolveUnicode::Loader()
{
    if(m_iniFile.empty())
        return false;
    if(!IniResolveFileAccess(this->m_iniFile))
        return false;
    //if(PathIsExists(m_iniFile.c_str()))
    char  detBuffer[4096]={0};
    HANDLE hFile=nullptr;
    return false;
}

bool IniResolveMultiByte::Loader()
{
    //
    if(m_iniFile.empty())
        return false;
    if(!IniResolveFileAccessA(this->m_iniFile))
        return false;
    //if(PathIsExists(m_iniFile.c_str()))
    char  detBuffer[4096]={0};
    HANDLE hFile=nullptr;
    return false;
}




bool SmapleCfgResolveUnicode::Loader()
{
    if(this->cfgFile.empty())
        return false;
    return true;
}