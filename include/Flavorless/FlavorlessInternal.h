/*********************************************************************************************************
* FlavorlessInternal.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_INTERNAL_H
#define FLAVORLESS_INTERNAL_H
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <stdio.h>

#ifdef _DEBUG
#ifndef assert
#include <cassert>
#endif
#define FLAVORASSERT(x) assert(x)
#else
#define FLAVORASSERT(x)
#endif

enum FlavorError{
    FLAVOR_OK=0,
    FLAVOR_UPDATE=1, ///some value was changed
    FLAVOR_INSERTED=2,////a new value
    ////
    FLAVOR_FAILED=-1,
    FLAVOR_NORMAL=-2,
    FLAVOR_FILE=-3
}

#define NEWLINE_CRLF "\r\n"
#define NEWLINE_CRLFW L"\r\n"
#define NEWLINE_LF "\n"
#define NEWLINE_LFW  L"\n"

#endif
