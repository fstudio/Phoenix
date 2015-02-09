/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: Http.c This File is Http Library Header
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHONEIX_PACKAGE_RUNTIME_HTTP_H
#define PHONEIX_PACKAGE_RUNTIME_HTTP_H
#include "rtdefs.h"
#include <stdbool.h>
typedef void* Request_t;


#define HTTP_RQ_METHOD_UNKNOWN 0x0001
#define HTTP_RQ_METHOD_GET 0x0002
#define HTTP_RQ_METHOD_HEAD 0x0004
#define HTTP_RQ_METHOD_POST 0x0008
#define HTTP_RQ_METHOD_PUT 0x0010
#define HTTP_RQ_METHOD_DELETE 0x0020
#define HTTP_RQ_METHOD_OPTIONS 0x0040
#define HTTP_RQ_METHOD_TRACE 0x0080
#define HTTP_RQ_METHOD_CONNECT  0x0100

typedef int(*ReceiveResponeCallBack)(char *p,size_t buffer,void* t);

PKG_BEGIN_DECL
////Feature.
PKGEXTERN char *PackageRuntimeStandardRequest(const char *ua,const char *host,unsigned method,const char *url,size_t *bufferSize,bool useSSL);
PKGEXTERN bool StandardRequest(const char *ua,const char *host,unsigned method,const char *url,bool useSSL,ReceiveResponeCallBack recallback);
PKGEXTERN void RequestBufferFree(void *p);
PKG_END_DECL


#endif
