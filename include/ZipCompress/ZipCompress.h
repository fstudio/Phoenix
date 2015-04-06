/*********************************************************************************************************
*   Phoneix ZipCompress Features
*   Note: ZipCompress.h
*   Date: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef ZIPCOMPRESS_H
#define ZIPCOMPRESS_H
#include <string>
#include <functional>
#include <Windows.h>
#include <ppltasks.h>

DWORD WINAPI ZipCompressThread(LPVOID lParam);

class ZipCompress{
    public:
        enum MessageReportCode{
            REPORT_FAILD=0,
            REPORT_WARNING=1,
            REPORT_ASK=2
        };
        ZipCompress(bool iskeep);
        ~ZipCompress();
        void SetMessageThrow(std::function<bool(std::wstring,int)> fun)
        {
            this->MessageThrow=fun;
        }
    private:
        int iRet;
        bool isdefault;
        std::function<bool(std::wstring,int)> MessageThrow;
    public:
        bool CreateCompressBuffer(BYTE* buffer,/**/size_t* bszie,std::wstring zipfile);
        bool CreateCompressBufferToBuffer(BYTE *buffer,size_t *bsize,BYTE *dest,size_t *dsize);
        bool CreateCompressFile(std::wstring sourcefile,/*OutDir*/std::wstring zipfile);
        bool UnCompressToBuffer(std::wstring zipfile,BYTE*dest,size_t *destlen);
        bool UnCompressToDisk(std::wstring zipfile,std::wstring folder);
};

////////By default ZipCompiressA use by PackageRuntime.
class ZipCompressA{
public:
    enum MessageReportCode{
        REPORT_FAILD=0,
        REPORT_WARNING=1,
        REPORT_ASK=2
    };
    ZipCompressA(bool iskeep);
    ~ZipCompressA();
    void SetMessageThrow(std::function<bool(std::string,int)> fun)
    {
        this->MessageThrow=fun;
    }
private:
    int iRet;
    bool isdefault;
    std::function<bool(std::string,int)> MessageThrow;
public:
    bool CreateCompressBuffer(BYTE* buffer,/**/size_t* bszie,std::string zipfile);
    bool CreateCompressBufferToBuffer(BYTE *buffer,size_t *bsize,BYTE *dest,size_t *dsize);
    bool CreateCompressFile(std::string sourcefile,/*OutDir*/std::string zipfile);
    bool UnCompressToBuffer(std::string zipfile,BYTE*dest,size_t *destlen);
    bool UnCompressToDisk(std::string zipfile,std::string folder);
};


//Asynchronous Compress:
class ZipAsynchronousCompress{
private:
    std::wstring filePath;
    std::function<bool(int)> NotifyFunction;
public:
    ZipAsynchronousCompress(std::wstring filepath);
    ~ZipAsynchronousCompress();
    void SetAsynchronousNotify(std::function<bool(int)> fun);
};

#endif
