#include <ZipCompress/ZipCompress.h>
#include "zlib.h"
#include "zip.h"
#include "unzip.h"
#include <fstream>
using namespace Concurrency;


static bool  InitializeZip()
{
    return true;
}

DWORD WINAPI ZipCompressThread(LPVOID lParam)
{
    return 0;
}


ZipCompress::ZipCompress(bool iskeep):iRet(0),isdefault(iskeep)
{
    //
    this->MessageThrow=nullptr;
    InitializeZip();
}

ZipCompress::~ZipCompress()
{
    //
}

bool ZipCompress::CreateCompressBuffer(BYTE* buffer,/**/size_t* bszie,std::wstring zipfile)
{
    if(buffer==nullptr)
        return false;
    return true;
}

bool ZipCompress::CreateCompressBufferToBuffer(BYTE *buffer,size_t *bsize,BYTE *dest,size_t *dsize)
{
    if(buffer==nullptr)
        return false;
    return true;
}

bool ZipCompress::CreateCompressFile(std::wstring sourcefile,/*OutDir*/std::wstring zipfile)
{
    if(_waccess_s(sourcefile.c_str(),4)!=0)
        return false;
    //
    if(_waccess_s(zipfile.c_str(),1)==0&&MessageThrow!=nullptr)
    {
         if(MessageThrow(L"The Zip File already exists, whether you need to replace ",REPORT_ASK))
         {
            //Delete File
            if(DeleteFileW(zipfile.c_str())!=TRUE)
                return false;
         }
    }
    return true;
}
bool ZipCompress::UnCompressToBuffer(std::wstring zipfile,BYTE*dest,size_t *destlen)
{
    if(_waccess_s(zipfile.c_str(),4)!=0)
        return false;//Not Find Zip File or  can't read
    return true;
}
bool ZipCompress::UnCompressToDisk(std::wstring zipfile,std::wstring folder)
{
    if(_waccess_s(zipfile.c_str(),4)!=0)
        return false;
    return true;
}

ZipAsynchronousCompress::ZipAsynchronousCompress(std::wstring filepath)
{

}

ZipAsynchronousCompress::~ZipAsynchronousCompress()
{

}

void ZipAsynchronousCompress::SetAsynchronousNotify(std::function<bool(int)> fun)
{
    ///
    this->NotifyFunction=fun;
}
