/*********************************************************************************************************
*   Phoneix Ini  Features
*   Note: IniResolve.cpp
*   Data: 2015.01.22
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef _WIN32
#error "Only Support Windows"
#endif
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wchar.h>
///MultiByteToUnicode
#include <Encoding/Encode.h>
#include <functional>
#include "IniResolve.hpp"

static const unsigned char bom_utf8[] = {0xEF,0xBB,0xBF};

static inline void IniResolveWriteMarker(HANDLE hFile,IniResolveFileEncoding encoding)
{
    DWORD dwBytesWritten;
    WCHAR bom;
    switch (encoding)
    {
    case INIRESOLVE_ENCODING_ANSI:
    case INIRESOLVE_ENCODING_UTF8_WITHOUTBOM:
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

////
bool IniResolveUnicode::ForeachReaderLineA()
{
    std::wstring ws;
    FILE *fp;
    char Line[65536]={0}; ///MaxLine.
    int nc;
    int i=0;
    if(_wfopen_s(&fp,this->m_iniFile.c_str(),L"rw")!=0)
        return false;
    ////Skip UTF-8 BOM
    if(this->codePage=65001)
    {
        fseek(fp,3L,SEEK_SET);
    }
    while(!feof(fp))
    {
        nc=fgetc(fp);
        if(nc==EOF)
        {
            break;
        }else{
            Line[i++]=static_cast<char>(nc);
        }
        switch(nc)
        {
            case '\r':
            Line[i--]='\0';
            break;
            case '\n':
            {
                Line[i--]='\0';
                this->GetTransactedLine(std::string(Line),ws);
                this->IniTextResolveAnalyzerLine(ws);
                i=0;
            }
            break;
            default:
            break;
        }
    }
    fclose(fp);
    return true;
}
bool IniResolveUnicode::ForeachReaderLineW()
{
    FILE *fp=nullptr;
    wchar_t Line[65536]={0}; ///MaxLine.
    int nc;
    int i=0;
    if(_wfopen_s(&fp,this->m_iniFile.c_str(),L"rw")!=0)
        return false;
    ////Skip UTF16BE LE BOM
    fseek(fp,2L,SEEK_SET);
    while(!feof(fp))
    {
        nc=fgetwc(fp);
        if(nc==WEOF)
        {
            break;
        }else{
            Line[i++]=static_cast<wchar_t>(nc);
        }
        switch(nc)
        {
            case '\r':
            Line[i--]='\0';
            break;
            case '\n':
            {
                Line[i--]='\0';
                this->IniTextResolveAnalyzerLine(Line,wcslen(Line));
                i=0;
            }
            break;
            default:
            break;
        }
    }
    fclose(fp);
    return true;
}
bool IniResolveUnicode::GetTransactedLine(std::string raw,std::wstring &det)
{
    det=MultiByteToUnicode(raw,this->codePage);
    return !det.empty();
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
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    hFile=CreateFileW(m_iniFile.c_str(),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    CloseHandle(hFile);
    if(mSize>0x4000000)//64MB
    {
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

////////////////////////////////////////////////////////////////
////MultiByte.

bool IniResolveMultiByte::GetTransactedLine(std::wstring raw,std::string &det)
{
    det=UnicodeToMultiByte(raw,codePage);
    return !det.empty();
}

bool IniResolveMultiByte::ForeachReaderLineA()
{
    FILE *fp;
    char Line[65536]={0}; ///MaxLine.
    int nc;
    int i=0;
    if(fopen_s(&fp,this->m_iniFile.c_str(),"rw")!=0)
        return false;
    ////Skip UTF-8 BOM
    if(this->codePage=65001)
    {
        fseek(fp,3L,SEEK_SET);
    }
    while(!feof(fp))
    {
        nc=fgetc(fp);
        if(nc==EOF)
        {
            break;
        }else{
            Line[i++]=static_cast<char>(nc);
        }
        switch(nc)
        {
            case '\r':
            Line[i--]='\0';
            break;
            case '\n':
            {
                Line[i--]='\0';
                this->IniTextResolveAnalyzerLine(Line,strlen(Line));
                i=0;
            }
            break;
            default:
            break;
        }
    }
    fclose(fp);
    return true;
}
bool IniResolveMultiByte::ForeachReaderLineW()
{
    FILE *fp=nullptr;
    wchar_t Line[65536]={0}; ///MaxLine.
    int nc;
    int i=0;
    std::string s;
    if(fopen_s(&fp,this->m_iniFile.c_str(),"rw")!=0)
        return false;
    ////Skip UTF16BE LE BOM
    fseek(fp,2L,SEEK_SET);
    while(!feof(fp))
    {
        nc=fgetwc(fp);
        if(nc==WEOF)
        {
            break;
        }else{
            Line[i++]=static_cast<wchar_t>(nc);
        }
        switch(nc)
        {
            case '\r':
            Line[i--]='\0';
            break;
            case '\n':
            {
                Line[i--]='\0';
                GetTransactedLine(std::wstring(Line),s);
                this->IniTextResolveAnalyzerLine(s);
                i=0;
            }
            break;
            default:
            break;
        }
    }
    fclose(fp);
    return true;
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
    hFile=CreateFileA(m_iniFile.c_str(),GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    CloseHandle(hFile);
    if(mSize>0x4000000)//64MB
    {
        ///

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