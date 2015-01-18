/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: Http.c This File is Http Library
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/Http.h>
#include <Windows.h>
#include <winhttp.h>
#include <wincrypt.h>



PKGEXTERN void SetUserAgent(const char *ua)
{

}

PKGEXTERN char* SendHttpRequest(unsigned method,const char* url,const char body)
{
   char *p=(char*)malloc(sizeof(char)*100);
   return p;
}
