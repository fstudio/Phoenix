/*********************************************************************************************************
*   Phoenix ZipProviders Features
*   Note: ZipProviders.cpp
*   Date: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Compression/ZipProviders.h>
#include "zlib.h"
#include "zip.h"
#include "unzip.h"
#include <fstream>
#include <io.h>
#include "Loki/ScopeGuard.h"
#include <atlstr.h>
#include <codecvt>

#define ZIP_GPBF_LANGUAGE_ENCODING_FLAG 0x800

using namespace Concurrency;

std::string GetStringFromUnicode(const std::wstring& src)
{
    std::locale sys_locale("");
    std::string retStr;
    const wchar_t* data_from = src.c_str();
    const wchar_t* data_from_end = src.c_str() + src.size();
    const wchar_t* data_from_next = 0;

    int wchar_size = 4;
    char* data_to = new char[(src.size() + 1) * wchar_size];
    char* data_to_end = data_to + (src.size() + 1) * wchar_size;
    char* data_to_next = 0;

    memset( data_to, 0, (src.size() + 1) * wchar_size );

    typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
    mbstate_t out_state = {0};
    auto result = std::use_facet<convert_facet>(sys_locale).out(
        out_state, data_from, data_from_end, data_from_next,
        data_to, data_to_end, data_to_next );
    if( result == convert_facet::ok)
    {
        retStr = data_to;
    }
    delete[] data_to;
    return retStr;
}
bool GetWideString( const std::string& src,std::wstring &wstr)
{
    std::locale sys_locale("");
    const char* data_from = src.c_str();
    const char* data_from_end = src.c_str() + src.size();
    const char* data_from_next = 0;

    wchar_t* data_to = new wchar_t[src.size() + 1];
    wchar_t* data_to_end = data_to + src.size() + 1;
    wchar_t* data_to_next = 0;

    wmemset( data_to, 0, src.size() + 1 );

    typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
    mbstate_t in_state = {0};
    auto result = std::use_facet<convert_facet>(sys_locale).in(
        in_state, data_from, data_from_end, data_from_next,
        data_to, data_to_end, data_to_next );
    if( result == convert_facet::ok )
    {
        wstr = data_to;
        delete[] data_to;
        return true;
    }
    delete[] data_to;
    return false;
}

std::string GetUTF8StringFromUnicode(const std::wstring &wstr)
{
    std::string u8str;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    u8str= conv.to_bytes(wstr);
    return u8str;
}

bool GetWideStringFromUTF8(const std::string &u8str,std::wstring &wstr)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
    wstr=conv.from_bytes(u8str);
    return true;
}

bool ZipAddFile(zipFile zf, LPCWSTR lpszFileNameInZip, LPCWSTR lpszFilePath, bool bUtf8 = false)
{
    DWORD dwFileAttr = GetFileAttributesW(lpszFilePath);
    if (dwFileAttr == INVALID_FILE_ATTRIBUTES){
        return false;
    }
    DWORD dwOpenAttr = (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0 ? FILE_FLAG_BACKUP_SEMANTICS : 0;
    HANDLE hFile = CreateFileW(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, dwOpenAttr, nullptr);
    if (hFile == INVALID_HANDLE_VALUE){
        return false;
    }

    LOKI_ON_BLOCK_EXIT(CloseHandle, hFile);
    FILETIME ftUTC, ftLocal;
    GetFileTime(hFile, nullptr, nullptr, &ftUTC);
    FileTimeToLocalFileTime(&ftUTC, &ftLocal);

    WORD wDate, wTime;
    FileTimeToDosDateTime(&ftLocal, &wDate, &wTime);

    zip_fileinfo FileInfo;
    ZeroMemory(&FileInfo, sizeof(FileInfo));
    FileInfo.dosDate = ((((DWORD)wDate) << 16) | (DWORD)wTime);
    FileInfo.external_fa |= dwFileAttr;
    std::wstring lfilezip=lpszFileNameInZip;
    if (bUtf8){
        std::string strFileNameInZipA = GetUTF8StringFromUnicode(lpszFileNameInZip);
        if (zipOpenNewFileInZip4(zf, strFileNameInZipA.c_str(),
            &FileInfo, NULL, 0, NULL, 0, NULL,
            Z_DEFLATED, 9,0, -MAX_WBITS, DEF_MEM_LEVEL,
            Z_DEFAULT_STRATEGY, NULL, 0, 0,
            ZIP_GPBF_LANGUAGE_ENCODING_FLAG) != ZIP_OK){
            return false;
        }
    }else{
        std::string strFileNameInZipA = GetStringFromUnicode(lfilezip);
        if(zipOpenNewFileInZip(zf, strFileNameInZipA.c_str(), &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9) != ZIP_OK){
            return false;
        }
    }
    LOKI_ON_BLOCK_EXIT(zipCloseFileInZip, zf);
    if ((dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0){
        return false;
    }
    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];
    LARGE_INTEGER li = {};
    if (!GetFileSizeEx(hFile, &li)){
        return false;
    }
    while (li.QuadPart > 0)
    {
        DWORD dwSizeToRead = li.QuadPart > (LONGLONG)BUFFER_SIZE ? BUFFER_SIZE : (DWORD)li.LowPart;
        DWORD dwRead = 0;
        if (!ReadFile(hFile, byBuffer, dwSizeToRead, &dwRead, nullptr)){
            return false;
        }
        if (zipWriteInFileInZip(zf, byBuffer, dwRead) < 0){
            return false;
        }
        li.QuadPart -= (LONGLONG)dwRead;
    }
    return true;
}

bool ZipAddFiles(zipFile zf, LPCWSTR lpszFileNameInZip, LPCWSTR lpszFiles, bool bUtf8 = false)
{
    WIN32_FIND_DATAW wfd;
    ZeroMemory(&wfd, sizeof(wfd));
    HANDLE hFind = FindFirstFileW(lpszFiles, &wfd);

    if (hFind == INVALID_HANDLE_VALUE){
        return false;
    }

    LOKI_ON_BLOCK_EXIT(FindClose, hFind);

    std::wstring strFilePath = lpszFiles;
    int nPos = strFilePath.rfind(L'\\');
    if (nPos !=std::string::npos){
        strFilePath = strFilePath.substr(nPos + 1);
    }else{
        strFilePath.clear();
    }
    std::wstring strFileNameInZip = lpszFileNameInZip;
    do
    {
        std::wstring strFileName = wfd.cFileName;

        if (strFileName == L"." || strFileName == L"..")
        {
            continue;
        }

        if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            std::wstring s=strFileNameInZip + strFileName + L"/";
            std::wstring s1=strFilePath + strFileName;
            if (!ZipAddFile(zf,s.c_str() ,s1.c_str() , bUtf8))
            {
                return false;
            }
            std::wstring s2=strFilePath + strFileName + L"\\*";
            if (!ZipAddFiles(zf,s.c_str(),s2.c_str(), bUtf8))
            {
                return false;
            }
        }
        else
        {
            std::wstring s3=strFileNameInZip + strFileName;
            std::wstring s4= strFilePath + strFileName;
            if (!ZipAddFile(zf,s3.c_str(),s4.c_str(), bUtf8))
            {
                return false;
            }
        }

    } while (FindNextFileW(hFind, &wfd));

    return true;
}

BOOL ZipExtractCurrentFile(unzFile uf, LPCWSTR lpszDestFolder)
{
    char szFilePathA[MAX_PATH];
    unz_file_info64 FileInfo;
    if (unzGetCurrentFileInfo64(uf, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0) != UNZ_OK)
    {
        return FALSE;
    }

    if (unzOpenCurrentFile(uf) != UNZ_OK)
    {
        return FALSE;
    }
    LOKI_ON_BLOCK_EXIT(unzCloseCurrentFile, uf);

    std::wstring strDestPath = lpszDestFolder;
    std::wstring strFileName;
    std::string filepathA=szFilePathA;
    if ((FileInfo.flag & ZIP_GPBF_LANGUAGE_ENCODING_FLAG) != 0)
    {

        GetWideStringFromUTF8(filepathA,strFileName);
        //strFileName = ANSIToUCS2(szFilePathA, CP_UTF8);
    }else{
        GetWideStringFromUTF8(filepathA,strFileName);
    }

    int nLength = strFileName.size();
    auto lpszFileName = strFileName.c_str();
    auto lpszCurrentFile = lpszFileName;
    //LOKI_ON_BLOCK_EXIT_OBJ(strFileName, &CString::ReleaseBuffer, -1);

    for (int i = 0; i <= nLength; ++i)
    {
        if (lpszFileName[i] == L'\0')
        {
            strDestPath += lpszCurrentFile;
            break;
        }

        if (lpszFileName[i] == '\\' || lpszFileName[i] == '/')
        {
            strDestPath += lpszCurrentFile;
            strDestPath += L"\\";

            CreateDirectoryW(strDestPath.c_str(), NULL);
            lpszCurrentFile = lpszFileName + i + 1;
        }
    }

    if (lpszCurrentFile[0] == L'\0')
    {
        return TRUE;
    }

    HANDLE hFile = CreateFileW(strDestPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
         return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(CloseHandle, hFile);

    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];

    while (true)
    {
        int nSize = unzReadCurrentFile(uf, byBuffer, BUFFER_SIZE);

        if (nSize < 0)
        {
            return FALSE;
        }
        else if (nSize == 0)
        {
            break;
        }
        else
        {
            DWORD dwWritten = 0;

            if (!WriteFile(hFile, byBuffer, (DWORD)nSize, &dwWritten, NULL) || dwWritten != (DWORD)nSize)
            {
                return FALSE;
            }
        }
    }

    FILETIME ftLocal, ftUTC;

    DosDateTimeToFileTime((WORD)(FileInfo.dosDate>>16), (WORD)FileInfo.dosDate, &ftLocal);
    LocalFileTimeToFileTime(&ftLocal, &ftUTC);
    SetFileTime(hFile, &ftUTC, &ftUTC, &ftUTC);
    return TRUE;
}




ZipCompress::ZipCompress(std::wstring &folder,std::wstring &file):m_folder(folder),m_file(file)
{
    //
}

void ZipCompress::AsynchronousProcess()
{
    if(_waccess_s(m_file.c_str(),4)!=0)
    {
        if(this->NotifyFunction!=0)
        {
            this->NotifyFunction(L"Raw File Not Found!",NOTIFY_FAILD,this->clientPtr);
        }
        return ;
    }
}

bool ZipCompress::ProcessContext()
{
    std::string strdest=GetStringFromUnicode(this->m_file);
    zipFile zf=zipOpen64(strdest.c_str(),0);
    bool bRet=true;
    if(zf==NULL)
        return false;
    if(!ZipAddFiles(zf,L"",this->m_folder.c_str(),FALSE)){
        bRet=false;
        goto Close;
    }
Close:
    zipClose(zf,NULL);
    return bRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ZipExtract::ZipExtract(std::wstring &folder,std::wstring &file):m_folder(folder),m_file(file)
{
    ///
}

void ZipExtract::AsynchronousProcess()
{
    if(_waccess_s(m_file.c_str(),4)!=0)
    {
        if(this->NotifyFunction!=0)
        {
            this->NotifyFunction(std::wstring(L"Zip File Not Found!"),NOTIFY_FAILD,this->clientPtr);
        }
        return ;
    }
}

bool ZipExtract::ProcessContext()
{
    std::string strSource=GetStringFromUnicode(this->m_file);
    unzFile uf=unzOpen64(strSource.c_str());
    if(uf==NULL)
        return false;
    bool bRet=true;
    unz_global_info64 gi;
    if(unzGetGlobalInfo64(uf,&gi)!=UNZ_OK)
    {
        bRet=false;
        goto Close;
    }
    CreateDirectoryW(this->m_folder.c_str(),NULL);
    if(!this->m_folder.empty()&&this->m_folder.at(this->m_folder.size()-1)!=L'\\')
    {
        this->m_folder+=L"\\";
    }
    for(int i=0;i<gi.number_entry;++i)
    {
        if (!ZipExtractCurrentFile(uf, this->m_folder.c_str()))
        {
            bRet= false;
            goto Close;
        }
        if (i < gi.number_entry - 1){
            if (unzGoToNextFile(uf) != UNZ_OK){
                bRet=false;
                goto Close;
            }
        }
    }
Close:
    unzClose(uf);
    return bRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool zipAddFileA(zipFile zf, LPCSTR lpszFileNameInZip, LPCSTR lpszFilePath)
{
    DWORD dwFileAttr = GetFileAttributesA(lpszFilePath);
    if (dwFileAttr == INVALID_FILE_ATTRIBUTES){
        return false;
    }
    DWORD dwOpenAttr = (dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0 ? FILE_FLAG_BACKUP_SEMANTICS : 0;
    HANDLE hFile = CreateFileA(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, dwOpenAttr, nullptr);
    if (hFile == INVALID_HANDLE_VALUE){
        return false;
    }
    FILETIME ftUTC, ftLocal;
    GetFileTime(hFile, nullptr, nullptr, &ftUTC);
    FileTimeToLocalFileTime(&ftUTC, &ftLocal);
    WORD wDate, wTime;
    FileTimeToDosDateTime(&ftLocal, &wDate, &wTime);
    zip_fileinfo FileInfo;
    ZeroMemory(&FileInfo, sizeof(FileInfo));
    FileInfo.dosDate = ((((DWORD)wDate) << 16) | (DWORD)wTime);
    FileInfo.external_fa |= dwFileAttr;
    bool bRet=true;
    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];
    LARGE_INTEGER li = {};
    if(zipOpenNewFileInZip(zf, lpszFileNameInZip, &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, 9) != ZIP_OK){
        bRet=false;
        goto Close;
     }
    if ((dwFileAttr & FILE_ATTRIBUTE_DIRECTORY) != 0){
        bRet=false;
        goto ZIPCloseLab;
    }
    if (!GetFileSizeEx(hFile, &li)){
        bRet=false;
        goto ZIPCloseLab;
    }
    while (li.QuadPart > 0)
    {
        DWORD dwSizeToRead = li.QuadPart > (LONGLONG)BUFFER_SIZE ? BUFFER_SIZE : (DWORD)li.LowPart;
        DWORD dwRead = 0;
        if (!ReadFile(hFile, byBuffer, dwSizeToRead, &dwRead, nullptr)){
            bRet=false;
            goto ZIPCloseLab;
        }
        if (zipWriteInFileInZip(zf, byBuffer, dwRead) < 0){
            bRet=false;
            goto ZIPCloseLab;
        }
        li.QuadPart -= (LONGLONG)dwRead;
    }
ZIPCloseLab:
    zipCloseFileInZip(zf);
Close:
    CloseHandle(hFile);
    return bRet;
}

bool zipAddFilesA(zipFile zf, LPCSTR lpszFileNameInZip, LPCSTR lpszFiles)
{
    WIN32_FIND_DATAA wfd;
    ZeroMemory(&wfd, sizeof(wfd));
    HANDLE hFind = FindFirstFileA(lpszFiles, &wfd);
    if (hFind == INVALID_HANDLE_VALUE){
        return false;
    }
    bool bRet=true;

    std::string strFilePath = lpszFiles;
    int nPos = strFilePath.rfind('\\');
    if (nPos !=std::string::npos){
        strFilePath = strFilePath.substr(nPos + 1);
    }else{
        strFilePath.clear();
    }
    std::string strFileNameInZip = lpszFileNameInZip;
    do
    {
        std::string strFileName = wfd.cFileName;

        if (strFileName == "." || strFileName == "..")
        {
            continue;
        }

        if ((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
        {
            std::string s=strFileNameInZip + strFileName + "/";
            std::string s1=strFilePath + strFileName;
            if (!zipAddFileA(zf,s.c_str() ,s1.c_str() ))
            {
                bRet=false;
                goto FINDCLOSELab;
            }
            std::string s2=strFilePath + strFileName + "\\*";
            if (!zipAddFilesA(zf,s.c_str(),s2.c_str()))
            {
                bRet=false;
                goto FINDCLOSELab;
            }
        }
        else
        {
            std::string s3=strFileNameInZip + strFileName;
            std::string s4= strFilePath + strFileName;
            if (!zipAddFileA(zf,s3.c_str(),s4.c_str()))
            {
                bRet=false;
                goto FINDCLOSELab;
            }
        }

    } while (FindNextFileA(hFind, &wfd));

FINDCLOSELab:
    FindClose(hFind);
    return bRet;
}
////////////////////////
bool zipExtractCurrentFileA(unzFile uf, LPCSTR lpszDestFolder)
{
    char szFilePathA[MAX_PATH];
    unz_file_info64 FileInfo;
    if (unzGetCurrentFileInfo64(uf, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0) != UNZ_OK)
    {
        return false;
    }

    if (unzOpenCurrentFile(uf) != UNZ_OK)
    {
        return false;
    }
    LOKI_ON_BLOCK_EXIT(unzCloseCurrentFile, uf);

    std::string strDestPath = lpszDestFolder;
    std::string filepathA=szFilePathA;

    int nLength = filepathA.size();
    auto lpszFileName = filepathA.c_str();
    auto lpszCurrentFile = lpszFileName;
    //LOKI_ON_BLOCK_EXIT_OBJ(strFileName, &CString::ReleaseBuffer, -1);

    for (int i = 0; i <= nLength; ++i)
    {
        if (lpszFileName[i] == '\0')
        {
            strDestPath += lpszCurrentFile;
            break;
        }

        if (lpszFileName[i] == '\\' || lpszFileName[i] == '/')
        {
            strDestPath += lpszCurrentFile;
            strDestPath += "\\";

            CreateDirectoryA(strDestPath.c_str(), NULL);
            lpszCurrentFile = lpszFileName + i + 1;
        }
    }

    if (lpszCurrentFile[0] == '\0')
    {
        return TRUE;
    }

    HANDLE hFile = CreateFileA(strDestPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
         return FALSE;
    }

    LOKI_ON_BLOCK_EXIT(CloseHandle, hFile);

    const DWORD BUFFER_SIZE = 4096;
    BYTE byBuffer[BUFFER_SIZE];

    while (true)
    {
        int nSize = unzReadCurrentFile(uf, byBuffer, BUFFER_SIZE);

        if (nSize < 0)
        {
            return FALSE;
        }
        else if (nSize == 0)
        {
            break;
        }
        else
        {
            DWORD dwWritten = 0;

            if (!WriteFile(hFile, byBuffer, (DWORD)nSize, &dwWritten, NULL) || dwWritten != (DWORD)nSize)
            {
                return FALSE;
            }
        }
    }

    FILETIME ftLocal, ftUTC;

    DosDateTimeToFileTime((WORD)(FileInfo.dosDate>>16), (WORD)FileInfo.dosDate, &ftLocal);
    LocalFileTimeToFileTime(&ftLocal, &ftUTC);
    SetFileTime(hFile, &ftUTC, &ftUTC, &ftUTC);
    return true;
}



bool ZipProvidersResolve(const char *dest,const char *source,ProvidersCallBack cb,void *date)
{
    unzFile uf=unzOpen64(source);
    bool bRet=true;
    unz_global_info64 gi;
    std::string deststr=dest;
    if(uf==NULL){
        cb(false,date);
        return false;
    }

    if(unzGetGlobalInfo64(uf,&gi)!=UNZ_OK)
    {
        bRet=false;
        goto Close;
    }
    CreateDirectoryA(dest,NULL);
    if(!deststr.empty()&&deststr.at(deststr.size()-1)!=L'\\')
    {
        deststr+="\\";
    }
    for(int i=0;i<gi.number_entry;++i)
    {
        if (!zipExtractCurrentFileA(uf, deststr.c_str()))
        {
            bRet= false;
            goto Close;
        }
        if (i < gi.number_entry - 1){
            if (unzGoToNextFile(uf) != UNZ_OK){
                bRet=false;
                goto Close;
            }
        }
    }
Close:
    unzClose(uf);
    cb(false,date);
    return bRet;
}


bool ZipProvidersCompress(const char *dest,const char *source,ProvidersCallBack cb,void *date)
{
    zipFile zf=zipOpen64(dest,0);
    bool bRet=true;
    if(zf==NULL)
        return false;
    if(!zipAddFilesA(zf,"",source)){
        bRet=false;
        goto Close;
    }
Close:
    zipClose(zf,NULL);
    cb(bRet,date);
    return bRet;
}

