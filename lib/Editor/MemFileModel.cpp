/*********************************************************************************************************
* MemFileMode.cpp
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoenix Memory File Model code
* E-mail:<forcemz@outlook.com>
* @2015.25
**********************************************************************************************************/
#include  <Editor/MemFileMode.h>
#include  <Editor/StorageFile.h>
/////

////////demo function
int  WINAPI ParserByteToLineMode(BYTE *b,size_t len)
{
    size_t i=0;
    size_t pre=0;
    bool stat=false;
    for(;i<len;i++)
    {
        while(b[i]=='\r'){
            if(i+1<len&&b[i+1]!='\n')
            {
                //New Line.
                pre=i;
            }else{
                stat=true;
            }
        }
        while(b[i]=='\n')
        {
            //*b[pre]; i-pre-1;
            stat=false;
            pre=i;
        }
    }
    return 0;
}

TextModelDocument::TextModelDocument():storefile(nullptr)
{
    ///
}

bool TextModelDocument::ParseStorageFile()
{
    return 0;
}
StorageFile *TextModelDocument::GetStorageFileFormIndex(unsigned index)
{
    if(index>=storeMap.size())
        return nullptr;
    return storeMap[index];
}
