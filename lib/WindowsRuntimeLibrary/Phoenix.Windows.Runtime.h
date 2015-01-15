/*********************************************************************************************************
* Phoenix.Windows.Runtime.h
* Copyright (C) 2014 The ForceStudio All Rights Reserved.
* Note: IShell Common Dialog.
* E-mail:<forcemz@outlook.com>
* @2014.08
**********************************************************************************************************/
#ifndef PHOENIX_WINDOWS_RUNTIME_H
#define PHOENIX_WINDOWS_RUNTIME_H

#ifndef  ENABLE_WINRT
#error This File Must Use Windows Runtime Properties
#endif
#include <Windows.h>
#if defined(_MSV_VER) &&(_MSC_VER>=1800)
#include <VersionHelpers.h>
#else
inline bool IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
    DWORDLONG        const dwlConditionMask = VerSetConditionMask(
        VerSetConditionMask(
        VerSetConditionMask(
            0, VER_MAJORVERSION, VER_GREATER_EQUAL),
               VER_MINORVERSION, VER_GREATER_EQUAL),
               VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);

    osvi.dwMajorVersion = wMajorVersion;
    osvi.dwMinorVersion = wMinorVersion;
    osvi.wServicePackMajor = wServicePackMajor;

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}
inline bool IsWindows8OrGreater()
{
    return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0);
}
#endif


inline bool CheckOSIsSupportWindowsRuntime()
{
    if (IsWindows8OrGreater())
    {
        return true;
    }
    return false;
}

//#include <windows.data.json.h>
//#include <windows.data.xml.dom.h>
//#include <windows.data.xml.xsl.h>
//must use Windows.winmd
using namespace Platform;
using namespace Windows::Data::Json;
using namespace Windows::Data::Xml::Dom;
using namespace Windows::Data::Xml::Xsl

/*
Compiler
/ZW enable WinRT language extensions  
/AI<dir> add to assembly search path  
  <dir> is the folder where the compiler searches the winmd files    
/FU<file> forced using assembly/module  
  force the inclusion of the specified winmd file  
/D "WINAPI_FAMILY=2"  
  set this define to compile against the ModernSDK subset of Win32  
Link
/APPCONTAINER[:NO]  
  marks the executable as runnable in the appcontainer (only)  
/WINMD[:{NO|ONLY}]  
  emits a winmd; if “ONLY” is specified, does not emit the executable, but just the winmd  
/WINMDFILE:filename  
  name of the winmd file to emit  
/WINMDDELAYSIGN[:NO]  
/WINMDKEYCONTAINER:name  
/WINMDKEYFILE:filename  
  used to sign the winmd  file  

*/

namespace Phoenix{
  ///
  class Objects{
  public:
    Objects();
  };
}

#endif

