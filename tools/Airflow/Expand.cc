/*********************************************************************************************************
* Expand.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"
#include <Windows.h>
#include <lzexpand.h>
#include <SetupAPI.h>



static UINT CALLBACK RecoverCallBack( PVOID context, UINT notification, UINT_PTR param1, UINT_PTR param2 )
{
    FILE_IN_CABINET_INFO_W *info = reinterpret_cast<FILE_IN_CABINET_INFO_W *>(param1);

    switch (notification)
    {
    case SPFILENOTIFY_FILEINCABINET:
    {
        LPCWSTR targetname = reinterpret_cast<LPCWSTR>(context);

        wcscpy_s( info->FullTargetName,MAX_PATH, targetname );
        return FILEOP_DOIT;
    }
    default: return NO_ERROR;
    }
}


UINT WINAPI RecoverMicrosoftStandaloneUpdatePackage(const wchar_t *szPackagePath,
    const wchar_t *szRecoverPath){
    if(_wcsicmp(szPackagePath,szRecoverPath)==0)
    {
        wprintf(L"Cannot extract file to itself!\nPackage: %ls \nRecover: %ls\n",szPackagePath,szRecoverPath);
        return 1;
    }
    return 0;
}

class GetTmpChar{
private:
    wchar_t *buffer;
public:
    GetTmpChar(const wchar_t *str):buffer(nullptr)
    {
        buffer=_wcsdup(str);
    }
    ~GetTmpChar(){
        if(buffer)
            free(buffer);
    }
    wchar_t *Get(){
        return buffer;
    }
};

UINT WINAPI RecoverCABPackage(const wchar_t *szPackagePath,const wchar_t *szRecoverPath)
{
    if(_wcsicmp(szPackagePath,szRecoverPath)==0)
    {
        wprintf(L"Cannot extract file to itself!\nPackage: %ls \nRecover: %ls\n",szPackagePath,szRecoverPath);
        return 1;
    }
    UINT comp;
    wchar_t szPath[4096]={0};
    if(!SetupGetFileCompressionInfoExW(szPackagePath,szPath,sizeof(szPath),NULL,NULL,NULL,&comp))
    {
        wprintf(L"can't open input file %ls\n",szPackagePath);
        return 1;
    }
    switch(comp)
    {
        case FILE_COMPRESSION_MSZIP:
        {
            GetTmpChar tmpchar(szRecoverPath);
            if(!SetupIterateCabinetW(szPackagePath,0,RecoverCallBack,tmpchar.Get()))
            {
                wprintf(L"cabinet extration failed: %ls\n",szPackagePath);
                return 1;
            }
        }
        break;
        case FILE_COMPRESSION_WINLZA:
        {
            INT hin,hout;
            OFSTRUCT ofin,ofout;
            LONG error;
            auto szPk=_wcsdup(szPackagePath);
            auto szRecover=_wcsdup(szRecoverPath);
            if((hin=LZOpenFileW(szPk,&ofin,OF_READ))<0)
            {
                wprintf(L"cannot open input file %ls\n",szPackagePath);
                free(szPk);
                free(szRecover);
                return 1;
            }
            if((hout=LZOpenFileW(szRecover,&ofout,OF_CREATE|OF_WRITE))<0)
            {
                LZClose(hin);
                wprintf(L"cannot open output file %ls\n",szRecoverPath);
                free(szPk);
                free(szRecover);
                return 1;
            }
            error=LZCopy(hin,hout);
            LZClose(hin);
            LZClose(hout);
            free(szPk);
            free(szRecover);
            if(error<0)
            {
                wprintf(L"LZCopy failed,error is %d\n",error);
                return 1;
            }
        }
        break;
        default:
        {
            if(!CopyFileW(szPackagePath,szRecoverPath,FALSE))
            {
                wprintf(L"CopyFileW failed\n");
                return 1;
            }
        }
        break;
    }
    return 0;
}

