/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: ZipArchive.h
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <ZipProviders/ZipProviders.h>
#include "ZipArchive.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

bool ZipCompress(const char *source,const char *dest)
{
    if(_access_s(source,04)!=0)
        return false;//This file not found
    return true;
}

bool ZipExtract(const char* zipfile,const char *path)
{
    return true;
}