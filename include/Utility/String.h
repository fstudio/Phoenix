/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmsys_String_h
#define cmsys_String_h


#include <stddef.h> /* size_t */

/* Redefine all public interface symbol names to be in the proper
   namespace.  These macros are used internally to kwsys only, and are
   not visible to user code.  Use kwsysHeaderDump.pl to reproduce
   these macros after making changes to the interface.  */

#if defined(__cplusplus)
extern "C"{
#endif

/**
 * Compare two strings ignoring the case of the characters.  The
 * integer returned is negative, zero, or positive if the first string
 * is found to be less than, equal to, or greater than the second
 * string, respectively.
 */
int Stringstrcasecmp(const char* lhs, const char* rhs);

/**
 * Identical to String_strcasecmp except that only the first n
 * characters are considered.
 */
int Stringstrncasecmp(const char* lhs, const char* rhs,
                                        size_t n);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
