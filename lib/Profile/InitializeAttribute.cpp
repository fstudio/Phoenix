/*********************************************************************************************************
* FlavorlessLoader.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <iostream>
#include <Profile/InitializeAttribute.hpp>
#include <ctype.h>
#define LINE_MAX_SIZE  8196
/*
typedef struct _INIFILE_CACHE {
    struct _INIFILE_CACHE *Next;
    ULONG EnvironmentUpdateCount;
    UNICODE_STRING NtFileName;
    PINIFILE_MAPPING_FILENAME FileMapping;
    HANDLE FileHandle;
    BOOLEAN WriteAccess;
    BOOLEAN UnicodeFile;
    BOOLEAN LockedFile;
    ULONG EndOfFile;
    PVOID BaseAddress;
    ULONG CommitSize;
    ULONG RegionSize;
    ULONG UpdateOffset;
    ULONG UpdateEndOffset;
    ULONG DirectoryInformationLength;
    FILE_BASIC_INFORMATION BasicInformation;
    FILE_STANDARD_INFORMATION StandardInformation;
} INIFILE_CACHE, *PINIFILE_CACHE;

typedef enum _INIFILE_OPERATION {
    FlushProfiles,
    ReadKeyValue,
    WriteKeyValue,
    DeleteKey,
    ReadKeyNames,
    ReadSectionNames,
    ReadSection,
    WriteSection,
    DeleteSection,
    RefreshIniFileMapping
} INIFILE_OPERATION;

typedef struct _INIFILE_PARAMETERS {
    INIFILE_OPERATION Operation;
    BOOLEAN WriteOperation;
    BOOLEAN Unicode;
    BOOLEAN ValueBufferAllocated;
    PINIFILE_MAPPING_FILENAME IniFileNameMapping;
    PINIFILE_CACHE IniFile;
    UNICODE_STRING BaseFileName;
    UNICODE_STRING FileName;
    UNICODE_STRING NtFileName;
    ANSI_STRING ApplicationName;
    ANSI_STRING VariableName;
    UNICODE_STRING ApplicationNameU;
    UNICODE_STRING VariableNameU;
    BOOLEAN MultiValueStrings;
    union {
        //
        // This structure filled in for write operations
        //
        struct {
            LPSTR ValueBuffer;
            ULONG ValueLength;
            PWSTR ValueBufferU;
            ULONG ValueLengthU;
        };
        //
        // This structure filled in for read operations
        //
        struct {
            ULONG ResultChars;
            ULONG ResultMaxChars;
            LPSTR ResultBuffer;
            PWSTR ResultBufferU;
        };
    };


    //
    // Remaining fields only valid when parsing an on disk .INI file mapped into
    // memory.
    //

    PVOID TextCurrent;
    PVOID TextStart;
    PVOID TextEnd;

    ANSI_STRING SectionName;
    ANSI_STRING KeywordName;
    ANSI_STRING KeywordValue;
    PANSI_STRING AnsiSectionName;
    PANSI_STRING AnsiKeywordName;
    PANSI_STRING AnsiKeywordValue;
    UNICODE_STRING SectionNameU;
    UNICODE_STRING KeywordNameU;
    UNICODE_STRING KeywordValueU;
    PUNICODE_STRING UnicodeSectionName;
    PUNICODE_STRING UnicodeKeywordName;
    PUNICODE_STRING UnicodeKeywordValue;
} INIFILE_PARAMETERS, *PINIFILE_PARAMETERS;

*/

static uint16_t ByteSwap(uint16_t i)
{
    uint16_t j;
    j =  (i << 8);
    j += (i >> 8);
    return j;
}

static inline void ByteSwapShortBuffer(WCHAR *buffer,int len)
{
    int i;
    uint16_t *sb=reinterpret_cast<uint16_t*>(buffer);
    for(i=0;i<len;i++)
        sb[i]=ByteSwap(sb[i]);
}

bool InitializeStructure::DeleteSection(const wchar_t *sec) {
    auto it = attrTable.find(sec);
    if (it != attrTable.end()) {
      if (it->second) {
        delete it->second;
      }
      attrTable.erase(it);
      isChanged = true;
      return true;
    }
    return false;
}

bool InitializeStructure::DeleteParameters(const wchar_t *sec, const wchar_t *key, int Order) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return false;
    auto iter = it->second->begin();
    auto end = it->second->end();
    auto index = 0;
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (index == Order) {
          it->second->items.erase(iter);
          isChanged = true;
          return true;
        }
        index++;
      }
      iter++;
    }
    return true;
}

///Get
std::wstring InitializeStructure::get(const wchar_t *sec, const wchar_t *key,
                   const wchar_t *preset, int Order ) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return preset;
    auto iter = it->second->begin();
    auto end = it->second->end();
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (Order == iter->nOrder) {
          return iter->value;
        }
      }
      iter++;
    }
    /// if(iter->second.)
    return preset;
}

bool InitializeStructure::set(const wchar_t *sec, const wchar_t *key, const wchar_t *value,
           int Order ) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return false;
    auto iter = it->second->begin();
    auto end = it->second->end();
    bool bSet = false;
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (Order == iter->nOrder) {
          iter->value = value;
          return true;
        }
        bSet = true;
      }
      iter++;
    }
    if (!bSet) {
      it->second->items.push_back(Parameters(key, value, std::wstring()));
    }
    /// if(iter->second.)
    return true;
}

bool InitializeStructure::InsertNewSection(const wchar_t *sec) {
    auto it = attrTable.find(sec);
    if (it != attrTable.end())
      return false;
    auto mSec = new IniSection();
    attrTable.insert(std::pair<std::wstring, decltype(mSec)>(sec, mSec));
    isChanged = true;
    return true;
}
/////
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
static inline int isSpace(wchar_t c)
{
    return isspace(c)||c==0x1A;
}

/////By ReactOS is use it ,but too many bugs.
//// so we not use it.
bool InitializeStructure::InitializeFileAnalysis(wchar_t *buffer,size_t size)
{
    if(!buffer||size==0)
        return false;
    auto nextline=const_cast<const wchar_t*>(buffer);
    std::wcout<<L"NextLine:\n"<<nextline<<std::endl;
    auto szEnd=const_cast<const wchar_t*>(buffer+size);
    const wchar_t *szLineStart,*szLineEnd;
    const WCHAR *szValueStart;
    wchar_t szStr[LINE_MAX_SIZE]={0};
    wchar_t szKey[LINE_MAX_SIZE]={0};
    wchar_t szValue[LINE_MAX_SIZE]={0};
    int line=0,len;
    bool bEscape=false;
    auto anonymous=new IniSection();
    auto currentSec=anonymous;
    while(nextline<szEnd)
    {
        szLineStart=nextline;
        nextline=reinterpret_cast<const wchar_t *>(memchr(szLineStart,'\n',szEnd-szLineStart));
        if(!nextline)nextline=reinterpret_cast<const wchar_t*>(memchr(szLineStart,'\r',szEnd-szLineStart));
        if(!nextline)nextline=szEnd;
        else nextline++;
        szLineEnd=nextline;
        line++;
        while(szLineStart<szLineEnd&&isSpace(*szLineStart))szLineStart++;
        while((szLineEnd>szLineStart)&&isSpace(szLineEnd[-1]))szLineEnd--;
        if(szLineStart>=szLineEnd)continue;
        if(*szLineStart=='[')
        {
            const WCHAR * szSectionEnd;
            if(!(szSectionEnd=reinterpret_cast<const wchar_t *>(memchr(szLineStart,']',szLineEnd-szLineStart))))
            {
                //// Failed.
            }else{
                szLineStart++;
                len=(int)(szSectionEnd-szLineStart);
                memset(szStr,0,LINE_MAX_SIZE*sizeof(WCHAR));
                memcpy(szStr,szLineStart,(len>LINE_MAX_SIZE?LINE_MAX_SIZE:len)*sizeof(WCHAR));
                currentSec=new IniSection();
                attrTable.insert(std::pair<std::wstring, decltype(currentSec)>(szStr, currentSec));
                continue;
            }
        }
        len=szLineEnd-szLineStart;
        if ((szValueStart = reinterpret_cast<const wchar_t*>(memchr( szLineStart, '=', szLineEnd - szLineStart ))) != NULL)
        {
            const WCHAR *szNameEnd = szValueStart;
            while ((szNameEnd > szLineStart) && isSpace(szNameEnd[-1])) szNameEnd--;
            len = szNameEnd - szLineStart;
            szValueStart++;
            while (szValueStart < szLineEnd && isSpace(*szValueStart)) szValueStart++;
        }
        if(len)
        {
            memset(szKey,0,LINE_MAX_SIZE*sizeof(WCHAR));
            memcpy(szKey,szLineStart,(len>LINE_MAX_SIZE?LINE_MAX_SIZE:len)*sizeof(WCHAR));
            if(szValueStart)
            {
                len=(int)(szLineEnd-szValueStart);
                if(len<LINE_MAX_SIZE-1)szValue[len]=0;
                else szValue[LINE_MAX_SIZE-1]=0;
                memcpy(szValue,szValueStart,(len>LINE_MAX_SIZE?LINE_MAX_SIZE-1:len)*sizeof(WCHAR));
            }
            Parameters pam(szKey,szValue,std::wstring(),0);
            currentSec->items.push_back(pam);
        }
    }
    return true;
}

////Note , this Initialize Analysis support space escape,and other.
bool InitializeStructure::InitializeFileAnalysisEx(wchar_t *buffer,size_t size)
{
    if(!buffer||szie=0)
        return false;
    IniSection *currentSec;
    int line=0;
    size_t index=0;
    ///GetLine
    ///Parser Line
    return true;
}

bool InitializeAttribute::SaveChanged()
{
    HANDLE hFile;
    hFile=CreateFileW(this->mfile.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    CloseHandle(hFile);
    return true;
}

bool InitializeAttribute::VirtualLoader()
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    bool bRet=true;
    WCHAR* szFile;
    LPVOID buffer=nullptr;
    LPSTR pBuffer;
    hFile=CreateFileW(this->mfile.c_str(),
        GENERIC_READ ,
        FILE_SHARE_READ | FILE_SHARE_WRITE|FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    ////Microsoft use NtAllocateVirtualMemory
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    auto mMax=(unsigned)-1;///this max 32bit
    if(mSize>(uint64_t)mMax*2)
    {
        ////Failed ,your vitual memory support this size file ?
    }
    auto mem=VirtualAlloc(NULL,(mSize+4)*sizeof(wchar_t),MEM_RESERVE,PAGE_READWRITE);
    //VirtualAlloc()
    ReadFile(hFile,mem,mSize,&mSize,NULL);
    //VirtualFree()
    VirtualFree(mem);
    return true;
}

bool InitializeAttribute::Loader()
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    bool bRet=true;
    WCHAR* szFile;
    LPVOID buffer=nullptr;
    LPSTR pBuffer;
    hFile=CreateFileW(this->mfile.c_str(),
        GENERIC_READ ,
        FILE_SHARE_READ | FILE_SHARE_WRITE|FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    ////Microsoft use NtAllocateVirtualMemory
    if(hFile==INVALID_HANDLE_VALUE)
    {
        return false;
    }
    GetFileSizeEx(hFile,&FileSize);
    auto mSize=FileSize.QuadPart;
    if((mSize>=0x8000000)||(mSize<=2))
    {
        CloseHandle(hFile);
        return this->VirtualLoader();//// this Parser to big file.
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
    if(dwFileSize>=3&&zm[0]==0xEF&&zm[1]==0xBB&&zm[2]==0xBF)
    {
        pBuffer=(char *)buffer+3;
        auto len=MultiByteToWideChar(CP_UTF8,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*sizeof(wchar_t));
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,buffer);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_UTF8, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.InitializeFileAnalysisEx(szFile,len);
        HeapFree(GetProcessHeap(),0,szFile);
        //this UTF8 with BOM
    }else if(zm[0]==0xFE&&zm[1]==0xFF) ///0xFEFF BE
    {
        szFile=(wchar_t*)buffer+2;
        ByteSwapShortBuffer(szFile,(dwFileSize-2)/sizeof(wchar_t));
        bRet=iniStructure.InitializeFileAnalysisEx(szFile,dwFileSize-2);
    }else if(zm[0]==0xFF&&zm[1]==0xFE) ///0xFFFE LE
    {
        szFile=(wchar_t*)buffer+2;
        bRet=iniStructure.InitializeFileAnalysisEx(szFile,dwFileSize-2);
        //
    }else{
        pBuffer=static_cast<char*>(buffer);
        auto len=MultiByteToWideChar(CP_ACP,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*sizeof(wchar_t));
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,buffer);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_ACP, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.InitializeFileAnalysisEx(szFile,len);
        HeapFree(GetProcessHeap(),0,szFile);
    }
    std::wcout<<L"Load Success"<<std::endl;
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
    if(nowTime!=this->lastTime)
        return false;
    return bRet&&(!isUpdate);
}