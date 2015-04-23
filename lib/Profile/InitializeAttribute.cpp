/*********************************************************************************************************
* FlavorlessLoader.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <Profile/InitializeAttribute.hpp>

static uint16_t ByteSwap(uint16_t i)
{
    unsigned short j;
    j =  (i << 8);
    j += (i >> 8);
    return j;
}

static inline void ByteSwapShortBuffer(WCHAR *buffer,int len)
{
    int i;
    uint16_t *sb=static_cast<uint16_t*>(buffer);
    for(i=0;i<len;i++)
        sb[i]=ByteSwap(sb[i]);
}


std::wstring InitializeStructure::Print() {
    std::wstringstream wstream;
    auto an = attrTable.find(ANONYMOUSSEC);
    if (an != attrTable.end()) {
      for (const auto &t : an->second->items) {
        wstream << t.key << L"=" << t.value << (isCRLF ? L"\r\n" : L"\n");
        if (!t.comments.empty())
          wstream << L"#" << t.comments << (isCRLF ? L"\r\n" : L"\n");
      }
    }
    for (const auto &it : attrTable) {
      if (it.first != ANONYMOUSSEC) {
        wstream << L"[" << it.first << L"]" << (isCRLF ? L"\r\n" : L"\n");
        for (auto &t : it.second->items) {
          wstream << t.key << L"=" << t.value << (isCRLF ? L"\r\n" : L"\n");
          if (!t.comments.empty()) {
            wstream << L"#" << t.comments << (isCRLF ? L"\r\n" : L"\n");
          }
        }
      }
    }
    return wstream.str();
}


bool InitializeStructure::InitializeFileAnalysis(wchar_t *buffer,size_t size)
{
    return true;
}

bool InitializeAttribute::LoadData()
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    bool bRet=true;
    WCHAR* szFile;
    LPVOID buffer=nullptr;
    LPSTR pBuffer;
    hFile=CreateFileW(this->mfile.c_str(),GENRIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    if(mSize>0x8000000||mSize=<2)
    {
        CloseHandle(hFile);
        return false;
    }
    auto dwFileSize=static_cast<DWORD>(mSize);
    buffer= HeapAlloc(GetProcessHeap(), 0 , dwFileSize); ///Big Memory.
    if(!buffer) ////HeapAlloc Failed
        return false;
    if(!ReadFile(hFile,buffer,dwFileSize,&dwFileSize,NULL))
    {
        HeapFree(GetProcessHeap(),0,buffer);
        ///WARN("Error %d reading file\n",GetLastError());
        CloseHandle(hFile);
        return false;
    }
    auto zm=static_cast<unsigned char*>(buffer);
    if(dwFileSize>=3&&zm[0]==0xEF&&zm[1]==BB&&zm[2]==BF)
    {
        pBuffer=(char *)buffer+3;
        auto len=MultiByteToWideChar(CP_UTF8,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*size(WCHAR));
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,mPtr);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_UTF8, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.InitializeFileAnalysis(szFile,len);
        HeapFree(GetProcessHeap(),0,szFile);
        //this UTF8 with BOM
    }else if(zm[0]==0xFE&&zm[1]==0xFF) ///0xFEFF BE
    {
        szFile=(wchar_t*)buffer+2;
        ByteSwapShortBuffer(szFile,(dwFileSize-2)/sizeof(wchar_t));
        bRet=iniStructure.InitializeFileAnalysis(szFile,dwFileSize-2);
    }else if(zm[0]==0xFF&&zn[1]=0xFE) ///0xFFFE LE
    {
        szFile=(wchar_t*)buffer+2;
        bRet=iniStructure.InitializeFileAnalysis(szFile,dwFileSize-2);
        //
    }else{
        pBuffer=static_cast<char*>(buffer);
        auto len=MultiByteToWideChar(CP_ACP,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*size(WCHAR));
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,mPtr);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_ACP, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.InitializeFileAnalysis(szFile,len);
        HeapFree(GetProcessHeap(),0,szFile);
    }
    CloseHandle(hFile);
    HeapFree(GetProcessHeap(),0,buffer);
    return bRet;
}

bool InitializeAttribute::GetFileAttributesZues(int64_t *now)
{
    WIN32_FILE_ATTRIBUTE_DATA attr_data;
    if(GetFileAttributesExW(mfile.c_str(),GetFileExInfoStandard,&attr_data)!=TRUE)
        return false;
    if(attr_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return false;
    }
    if ( (attr_data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) && 2 ) {
        return false;
    }
    auto &ft=attr_data.ftLastWriteTime;
    ULARGE_INTEGER ularge;
    ularge.LowPart = ft.dwLowDateTime;
    ularge.HighPart = ft.dwHighDateTime;
    if(now)
        {
            *now=ularge.QuadPart;
        }else{
            this->lastTime=ularge.QuadPart;
        }
    return true;
}


bool InitializeAttribute::EffectiveAutoChecker()
{
    return GetFileAttributesZues();
}

bool InitializeAttribute::IsUpdated()
{
    int64_t nowTime=0;
    auto bRet=GetFileAttributesZues(&nowTime);
    return (!bRet||(nowTime!=this->lastTime)||IsUpdated);
}