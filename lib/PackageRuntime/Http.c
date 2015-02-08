/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: HTTP.c This File is Http Library
*   Data: 2015.01.13
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/HTTP.h>
#include <Windows.h>
#include <winhttp.h>
#include <wincrypt.h>



PKGEXTERN void SetUserAgent(const char *ua,Request_t request)
{
    if(request==NULL)
        return ;
    ///
}

PKGEXTERN char* SendHttpRequest(unsigned method,const char* url,const char body)
{
   char *p=(char*)malloc(sizeof(char)*100);
   return p;
}
