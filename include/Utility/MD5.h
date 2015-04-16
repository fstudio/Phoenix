/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmsys_MD5_h
#define cmsys_MD5_h


#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * MD5 state data structure.
 */
typedef struct kwsysMD5_s kwsysMD5;

/**
 * Create a new MD5 instance.  The returned instance is not initialized.
 */
kwsysMD5* kwsysMD5_New(void);

/**
 * Delete an old MD5 instance.
 */
void kwsysMD5_Delete(kwsysMD5* md5);

/**
 * Initialize a new MD5 digest.
 */
void kwsysMD5_Initialize(kwsysMD5* md5);

/**
 * Append data to an MD5 digest.  If the given length is negative,
 * data will be read up to but not including a terminating null.
 */
void kwsysMD5_Append(kwsysMD5* md5, unsigned char const* data,
                                 int length);

/**
 * Finalize a MD5 digest and get the 16-byte hash value.
 */
void kwsysMD5_Finalize(kwsysMD5* md5, unsigned char digest[16]);

/**
 * Finalize a MD5 digest and get the 32-bit hexadecimal representation.
 */
void kwsysMD5_FinalizeHex(kwsysMD5* md5, char buffer[32]);

/**
 * Convert a MD5 digest 16-byte value to a 32-byte hexadecimal representation.
 */
void kwsysMD5_DigestToHex(unsigned char const digest[16],
                                      char buffer[32]);

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
