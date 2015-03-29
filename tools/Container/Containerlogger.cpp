/*********************************************************************************************************
* Containerlogger.cpp
* Note: Phoenix Container
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "ContainerAPI.h"

static FILE *logfp=nullptr;

static bool SetDefaultLogger()
{
    wchar_t temp[4096]={0};
    if(GetTempPathW(256,temp)==0)
    return false;/// This Function invoke failed.
#if defined(_MSC_VER)&& _MSC_VER>=1400
    wcscat_s(temp,4096,L"/Phoenix.tools.Container.defualt.v1.log");
    if(_wfopen_s(&logfp,temp,L"a+")!=0)
        return false;
#else
    wcscat(temp,L"/Phoenix.tools.Container.defualt.v1.log");
    if((logfp=wfopen(temp,L"a+"))==nullptr)
        return false;
#endif
    return true;
}

bool InitializeLogger()
{
    return SetDefaultLogger();
}

void LoggerDestory()
{
    if(logfp)
        fclose(logfp);
}

void TRACEWithFile(FILE *fp,const wchar_t* format,...)
{
  if(fp!=nullptr)
  {
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfwprintf_s(fp, format, ap);
    va_end(ap);
  }
}
void TRACE(const wchar_t* format,...)
{
  if(logfp!=nullptr)
  {
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfwprintf_s(logfp, format, ap);
    va_end(ap);
  }
}

