#ifndef ZIPCOMPRESS_H
#define ZIPCOMPRESS_H
#include <string>
#include <Windows.h>
#include <ppltasks.h>

DWORD WINAPI ZipCompressThread(LPVOID lParam);

class ZipCompress{
    public:
        ZipCompress();
        ~ZipCompress();
    private:
        int iRet;
    public:
        bool CreateCompressBuffer(BYTE* buffer,/**/size_t* bszie,std::wstring zipfile);
        bool CreateCompressBufferToBuffer(BYTE *buffer,size_t *bsize,BYTE *dest,size_t *dsize);
        bool CreateCompressFile(std::wstring sourcefile,/*OutDir*/std::wstring zipfile);
        bool UnCompressToBuffer(std::wstring zipfile,BYTE*dest,size_t *destlen);
        bool UnCompressToDisk(std::wstring zipfile,std::wstring folder);
};

//Asynchronous Compress:
class ZipAsynchronousCompress{
public:
    ZipAsynchronousCompress();
    ~ZipAsynchronousCompress();
};

#endif
