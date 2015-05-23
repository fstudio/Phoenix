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
#include <list>
#define LINE_MAX_SIZE  8196
#define MAX_FILE_VIRTUALMEMSIZE 0x100000000
#define MAX_FILE_NOVIRTUALMEMSIZE 0x10000000

class wcharget{
private:
    wchar_t *wstr;
public:
    wcharget(const char *str):wstr(nullptr)
    {
        if(str==nullptr)
            return ;
        size_t len =strlen(str);
        int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
        if(unicodeLen==0)
            return ;
        this->wstr = new wchar_t[unicodeLen + 1];
        memset(this->wstr, 0, (unicodeLen + 1) * sizeof(wchar_t));
        ::MultiByteToWideChar(CP_ACP, 0,str, -1, (LPWSTR)this->wstr,unicodeLen);
    }
    const wchar_t *Get()
    {
        if(!wstr)
            return nullptr;
        return const_cast<const wchar_t *>(wstr);
    }
    ~wcharget()
    {
        if(wstr)
            delete[] wstr;
    }
};
/*
LF U+000A
VT U+000B
FF U+000C
CR U+000D
CR+LF U+000D+LF U+000A
NEL U+0085
LS U+2028
PS U+2029
*/
enum NewLineType{
    NewLine_CRLF=0, ///New Line CRLF is a ISO
    NewLine_LF=1,//Unix like system use it
    NewLine_CR=2//Old Apple Ma
};

template <typename T>
struct MoveLine{
    T beigin;
    T end;
    int newLine;
    MoveLine(T b,T e,int ne=0):begin(b),end(e),newLine(ne){}
    MoveLine<T> &operator =(const MoveLine<T> &ml)
    {
        begin=ml.begin;
        end=ml.end;
        newLine=ml.newLine;
    }
    MoveLine<T> &operator==(const MoveLine<T> &ml)
    {
        return (begin==ml.begin&&end==ml.end&&newLine==ml.newLine);
    }
};
///Portability At ABI Boundaries (Modern C++)
//Boundaries
static  int isspace(int c)
{
    return c==' '||(unsigned)c-'\t'<5;
}
static int iswspace(wint_t wc)
{
    static const wchar_t spaces[] = {
        ' ', '\t', '\n', '\r', 11, 12,  0x0085,
        0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005,
        0x2006, 0x2008, 0x2009, 0x200a,
        0x2028, 0x2029, 0x205f, 0x3000, 0
    };
    return wc && wcschr(spaces, wc);
}
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

bool InitializeStructure::FiniteStateMachineAnalysis(wchar_t *buffer,size_t size,int separator)
{
    wchar_t *p=buffer;
    wchar_t *end=buffer+size;
    wchar_t *secStart=nullptr;
    wchar_t *keyStart=nullptr;
    wchar_t *valueStart=nullptr;
    auto anonymous=new IniSection();
    auto currentSec=anonymous;
    setlocale(LC_ALL, NULL);
    enum _FSMState{
        STAT_NONE=0,
        STAT_SECTION,
        STAT_KEY,
        STAT_VALUE,
        STAT_COMMENT
    }state=STAT_NONE;
    for(;p<end;p++)
    {
        switch(state)
        {
            case STAT_NONE:
            {
                if(*p==L'[')
                {
                    state=STAT_SECTION;
                    secStart=p+1;
                }else if(*p=='#'||*p==';')
                {
                    state=STAT_COMMENT;
                }else if(!iswspace(*p)){
                    state=STAT_KEY;
                    keyStart=p;
                }
                break;
            }
            case STAT_SECTION:
            {
                if(*p==']')
                {
                    *p='\0';
                    currentSec=new IniSection();
                    std::wstring wsec=secStart;
                    attrTable.insert(std::pair<std::wstring, decltype(currentSec)>(wsec, currentSec));
                    state=STAT_NONE;
                }
                break;
            }
            case STAT_COMMENT:
            {
                if(*p=='\n')
                {
                    state=STAT_NONE;
                    break;
                }
                break;
            }
            case STAT_KEY:
            {
                if(*p==separator||*p=='\t')
                {
                    *p='\0';
                    state=STAT_VALUE;
                    valueStart=p+1;
                }
                break;
            }
            case STAT_VALUE:
            {
                if(*p=='\n'||*p=='\r')
                {
                    *p='\0';
                    std::wstring ke=keyStart;
                    std::wstring va=valueStart;
                    Parameters pam(ke,va,std::wstring(),0);
                    currentSec->items.push_back(pam);
                    state=STAT_NONE;
                }
                break;
            }
            default:
            break;
        }
    }
    if(state==STAT_VALUE)
    {
        ////
        std::wstring ke=keyStart;
        std::wstring va=valueStart;
        Parameters pam(ke,va,std::wstring(),0);
        currentSec->items.push_back(pam);
    }
    return true;
}

bool InitializeStructure::FiniteStateMachineAnalysis(char *buffer,size_t size,int separator,int codepage)
{
    char *p=buffer;
    char *end=buffer+size;
    char *secStart=nullptr;
    char *keyStart=nullptr;
    char *valueStart=nullptr;
    auto anonymous=new IniSection();
    auto currentSec=anonymous;
    enum _FSMState{
        STAT_NONE=0,
        STAT_SECTION,
        STAT_KEY,
        STAT_VALUE,
        STAT_COMMENT
    }state=STAT_NONE;
    for(;p<end;p++)
    {
        switch(state)
        {
            case STAT_NONE:
            {
                if(*p==L'[')
                {
                    state=STAT_SECTION;
                    secStart=p+1;
                }else if(*p=='#'||*p==';')
                {
                    state=STAT_COMMENT;
                }else if(!isspace(*p)){
                    state=STAT_KEY;
                    keyStart=p;
                }
                break;
            }
            case STAT_SECTION:
            {
                if(*p==']')
                {
                    *p='\0';
                    std::string ke=keyStart;
                    std::string va=valueStart;
                    wcharget k(ke.c_str());
                    wcharget v(va.c_str());
                    Parameters pam(std::wstring(k.Get()),std::wstring(v.Get()),std::wstring(),0);
                    currentSec->items.push_back(pam);
                    state=STAT_NONE;
                }
                break;
            }
            case STAT_COMMENT:
            {
                if(*p=='\n')
                {
                    state=STAT_NONE;
                    break;
                }
                break;
            }
            case STAT_KEY:
            {
                if(*p==separator||*p=='\t')
                {
                    *p='\0';
                    state=STAT_VALUE;
                    valueStart=p+1;
                }
                break;
            }
            case STAT_VALUE:
            {
                if(*p=='\n'||*p=='\r')
                {
                    *p='\0';
                    std::string ke=keyStart;
                    std::string va=valueStart;
                    wcharget k(ke.c_str());
                    wcharget v(va.c_str());
                    Parameters pam(std::wstring(k.Get()),std::wstring(v.Get()),std::wstring(),0);
                    state=STAT_NONE;
                }
                break;
            }
            default:
            break;
        }
    }
    if(state==STAT_VALUE)
    {
        ////
        std::string ke=keyStart;
        std::string va=valueStart;
        wcharget k(ke.c_str());
        wcharget v(va.c_str());
        Parameters pam(std::wstring(k.Get()),std::wstring(v.Get()),std::wstring(),0);
    }
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
    //////We don't known this file uncoding,and load this size ...
    auto mem=VirtualAlloc(NULL,(mSize+4),MEM_RESERVE,PAGE_READWRITE);
    //VirtualAlloc()
    DWORD zSize=UINT32_MAX;
    auto imSize=mSize;
    if(mSize>zSize)
    {
        wchar_t* mp=static_cast<wchar_t *>(mem);
        while(imSize>zSize)
        {
            ReadFile(hFile,mp,zSize,&zSize,NULL);
            mp+=zSize;
            imSize-=zSize;
        }
        if(imSize<=zSize)
        {
            DWORD dmSize=static_cast<DWORD>(imSize);
            ReadFile(hFile,mem,dmSize,&dmSize,NULL);
        }
    }else{
        DWORD dmSize=static_cast<DWORD>(mSize);
        ReadFile(hFile,mem,dmSize,&dmSize,NULL);
    }
    //VirtualFree()
    VirtualFree(mem,0,MEM_RELEASE);
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
    if(mSize>=MAX_FILE_VIRTUALMEMSIZE||(mSize<=2))
    {
        CloseHandle(hFile);
        return false;//// this file size is to big, now we not support it.or empty file
    }else if(mSize>MAX_FILE_NOVIRTUALMEMSIZE)
    {
        CloseHandle(hFile); ///256MB~4GB size
        return this->VirtualLoader();
    }
    auto dwFileSize=static_cast<DWORD>(mSize);
    ///Because rea
    buffer= HeapAlloc(GetProcessHeap(), 0 , dwFileSize+1); ///Big Memory.
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
    zm[dwFileSize]='\0';
    if(dwFileSize>=3&&zm[0]==0xEF&&zm[1]==0xBB&&zm[2]==0xBF)
    {
        pBuffer=(char *)buffer+3;
        auto len=MultiByteToWideChar(CP_UTF8,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*sizeof(wchar_t)+1);
        szFile[len]='\0';
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,buffer);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_UTF8, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.FiniteStateMachineAnalysis(szFile,len);
        HeapFree(GetProcessHeap(),0,szFile);
        //this UTF8 with BOM
    }else if(zm[0]==0xFE&&zm[1]==0xFF) ///0xFEFF BE
    {
        szFile=(wchar_t*)buffer+2;
        ByteSwapShortBuffer(szFile,(dwFileSize-2)/sizeof(wchar_t));
        bRet=iniStructure.FiniteStateMachineAnalysis(szFile,dwFileSize-2);
    }else if(zm[0]==0xFF&&zm[1]==0xFE) ///0xFFFE LE
    {
        szFile=(wchar_t*)buffer+2;
        //MessageBoxW(nullptr,szFile,L"Buffer",MB_OK);
        bRet=iniStructure.FiniteStateMachineAnalysis(szFile,dwFileSize-2);
        //
    }else{
        pBuffer=static_cast<char*>(buffer);
        auto len=MultiByteToWideChar(CP_ACP,0,const_cast<const char*>(pBuffer),dwFileSize,NULL,0);
        szFile=(wchar_t*)HeapAlloc(GetProcessHeap(),0,len*sizeof(wchar_t)+1);
        szFile[len]='\0';
        if(!szFile)
        {
            HeapFree(GetProcessHeap(),0,buffer);
            CloseHandle(hFile);
            return false;
        }
        MultiByteToWideChar(CP_ACP, 0, const_cast<const char*>(pBuffer), dwFileSize, szFile, len);
        bRet=iniStructure.FiniteStateMachineAnalysis(szFile,len);
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
    if(nowTime!=this->lastTime)
        return false;
    return bRet&&(!isUpdate);
}