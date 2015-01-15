/*********************************************************************************************************
* PhoenixUniversalChardet.cpp
* Thanks Mozilla Foundation
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#include <Phoenix.h>
#include <string>
#include <UniversalChardet/UniversalChardet.h>
#include "base/nsUniversalDetector.h"


UniversalChardet::UniversalChardet(std::string Content)
{
    ///
    if(Content.empty())
        return ;
}


extern "C" const char* UniversalGetCharSet(const char *text,size_t len)
{
    return nullptr;
}
