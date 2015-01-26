/*********************************************************************************************************
* StorageFile.h
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoenix StorageFile header
* E-mail:<forcemz@outlook.com>
* @2015.25
**********************************************************************************************************/
#ifndef PHOENIX_EDIT_STOREFILE_H
#define PHOENIX_EDIT_PHYSICS_H
#ifndef _PHOENIX_BASE_
#include <Phoenix.h>
#endif

class StorageFile{
private:
    uint64_t mSize;//Byte
    std::wstring m_relPath;
    wchar_t* mFilePtr;
    bool IsModified;
    unsigned originEncoding;
    bool OriginEncodingDeter();
public:
    StorageFile(std::wstring relPath);
    ~StorageFile();
    bool LoadFile();
    std::wstring FormatTextOut();
    wchar_t *GetMemoryPtr(){return mFilePtr;}
    uint64_t GetFilePtrSize(){return mSize;}
    unsigned GetOriginEncoding(){return this->originEncoding;}
    bool ConvertEncodingSava(unsigned encoding);
protected:
    bool GetStoreFileSize();
};



#endif