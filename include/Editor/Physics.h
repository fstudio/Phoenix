/*********************************************************************************************************
* PhoenixInterface.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Phoenix Interface header
* E-mail:<forcemz@outlook.com>
* @2014.09
**********************************************************************************************************/
#ifndef PHOENIX_EDIT_PHYSICS_H
#define PHOENIX_EDIT_PHYSICS_H
#ifndef _PHOENIX_BASE_
#include <Phoenix.h>
#endif

class PhEditPhysicsFile{
private:
    uint64_t mSize;//Byte
    std::wstring rePath;
    wchar_t* mFilePtr;
    bool IsModified;
public:
    PhEditPhysicsFile();
    ~PhEditPhysicsFile();
    bool LoadPhysicsFile();
    std::wstring FormatPhysicsTextOut();
	wchar_t *GetMemoryPtr(){return mFilePtr;}
protected:
    bool GetPhysicsFileSize();
};



#endif