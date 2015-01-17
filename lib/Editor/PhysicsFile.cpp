/*********************************************************************************************************
* PhEditPhysicsFile.cpp
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note:
* E-mail:<forcemz@outlook.com>
* @2014.09
**********************************************************************************************************/
#include <Phoenix.h>
#include <stdint.h>
#include <string>
#include <map>
#define MAX_MAP_SIZE_FILE 64*1024*1024*16

#include <Editor/Physics.h>

std::map<int,PhEditPhysicsFile> PhfileMap;






bool PhEditPhysicsFile::GetPhysicsFileSize()
{
    HANDLE hFile;
    LARGE_INTEGER FileSize;
    hFile=CreateFileW(rePath.c_str(),GENRIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUE_NORMAL,NULL);
    if(hFile!=INVALID_HANDLE_VALUE)
    {
        GetFileSizeEx(hFile,&FileSize);
        this->mSize=FileSize.QuadPart;
        CloseHandle(hFile);
    }else{
        //CreateFileW New
    }
    if(mSize>0x4000000) //64MByte
        return false;
    return true;
}

bool PhEditPhysicsFile::LoadPhysicsFile()
{
    if(!this->GetPhysicsFileSize())
    {
        return false;
    }
    mFilePtr=new int16_t [mSize/2+1];
    //ReadFile()
    //ReadFileEx()
    return true;
}

PhEditPhysicsFile::~PhEditPhysicsFile():mSize(0),IsModified(false)
{
    if(!mFilePtr)
    {
        delete[] mFilePtr;
    }
}