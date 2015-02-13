/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmsys_Encoding_h
#define cmsys_Encoding_h

#include <wchar.h>


#if defined(__cplusplus)
extern "C"
{
#endif


/* Convert a narrow string to a wide string.
   On Windows, UTF-8 is assumed, and on other platforms,
   the current locale is assumed.
   */
size_t kwsysEncoding_mbstowcs(wchar_t* dest, const char* src, size_t n);

/* Convert a narrow string to a wide string.
   This can return NULL if the conversion fails. */
wchar_t* kwsysEncoding_DupToWide(const char* src);


/* Convert a wide string to a narrow string.
   On Windows, UTF-8 is assumed, and on other platforms,
   the current locale is assumed. */
size_t kwsysEncoding_wcstombs(char* dest, const wchar_t* src, size_t n);

/* Convert a wide string to a narrow string.
   This can return NULL if the conversion fails. */
 char* kwsysEncoding_DupToNarrow(const wchar_t* str);


#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif
