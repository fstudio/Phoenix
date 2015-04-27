/*********************************************************************************************************
* StorageFile.cpp
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoenix StorageFile Code
* E-mail:<forcemz@outlook.com>
* @2015.25
**********************************************************************************************************/
#include <Phoenix.h>
#include <stdint.h>
#include <string>
#include <map>
#define MAX_MAP_SIZE_FILE 64*1024*1024*16

#include <Editor/StorageFile.h>
#include <UniversalChardet/UniversalChardet.h>


StorageFile::StorageFile(std::wstring relPath):m_relPath(relPath),mSize(0),IsModified(false),mFilePtr(nullptr)
{
    ///
}
StorageFile::~StorageFile()
{
    if(!mFilePtr)
    {
        delete[] mFilePtr;
    }
}

bool StorageFile::OriginEncodingDeter()
{
    return false;
}

bool StorageFile::ConvertEncodingSava(unsigned encoding)
{
    switch(encoding)
    {
        default:
        break;
    }
    return false;
}

bool StorageFile::GetStoreFileSize()
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    hFile=CreateFileW(rePath.c_str(),GENRIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile!=INVALID_HANDLE_VALUE)
    {
        GetFileSizeEx(hFile,&FileSize);
        this->mSize=FileSize.QuadPart;
        CloseHandle(hFile);
    }else{
        //CreateFileW New
        return false;
    }
    if(mSize>0x10000000) 
        return false;
    return true;
}

bool StorageFile::LoadFile()
{
    if(!this->GetStoreFileSize())
    {
        return false;
    }
    mFilePtr=new int16_t [mSize/2+1];
    //ReadFile()
    //ReadFileEx()
    return true;
}
