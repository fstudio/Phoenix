/*********************************************************************************************************
* Phoenix.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: Application->Entry
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#ifndef _PHOENIX_BASE_
#define _PHOENIX_BASE_
#pragma once

#ifdef _WIN32
#include "Platform/Win32/PhoenixWindows.h"
#define PHOENIXEDITOR  L"Phoenix.Editor"
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#define UNC_MAX_PATH   32767
#define MAX_TASK_CHILD 5



#elif __unix__
#include "Platform/POSIX/PhoenixPosix.h"
#define PHOENIXEDITOR "Phoenix.Editor"

#endif


typedef struct VersionTags_{
   unsigned marjo;
   unsigned min;
   unsigned patch;
   unsigned buildtimes;
}version_t;

typedef DWORD (WINAPI *ExecuteFunction)(
    LPVOID lpThreadParameter
    );

#endif

