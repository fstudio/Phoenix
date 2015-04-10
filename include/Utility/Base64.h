/*============================================================================
  KWSys - Kitware System Library
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmsys_Base64_h
#define cmsys_Base64_h


#include <stddef.h> /* size_t */



#if defined(__cplusplus)
extern "C"
{
#endif

/**
 * Encode 3 bytes into a 4 byte string.
 */
 void KwBase64_Encode3(const unsigned char *src,
                                     unsigned char *dest);

/**
 * Encode 2 bytes into a 4 byte string.
 */
void KwBase64_Encode2(const unsigned char *src,
                                     unsigned char *dest);

/**
 * Encode 1 bytes into a 4 byte string.
 */
void KwBase64_Encode1(const unsigned char *src,
                                     unsigned char *dest);

/**
 * Encode 'length' bytes from the input buffer and store the encoded
 * stream into the output buffer. Return the length of the encoded
 * buffer (output). Note that the output buffer must be allocated by
 * the caller (length * 1.5 should be a safe estimate).  If 'mark_end'
 * is true than an extra set of 4 bytes is added to the end of the
 * stream if the input is a multiple of 3 bytes.  These bytes are
 * invalid chars and therefore they will stop the decoder thus
 * enabling the caller to decode a stream without actually knowing how
 * much data to expect (if the input is not a multiple of 3 bytes then
 * the extra padding needed to complete the encode 4 bytes will stop
 * the decoding anyway).
 */
size_t KwBase64_Encode(const unsigned char *input,
                                      size_t length,
                                      unsigned char *output,
                                      int mark_end);

/**
 * Decode 4 bytes into a 3 byte string.  Returns the number of bytes
 * actually decoded.
 */
int KwBase64_Decode3(const unsigned char *src,
                                    unsigned char *dest);

/**
 * Decode bytes from the input buffer and store the decoded stream
 * into the output buffer until 'length' bytes have been decoded.
 * Return the real length of the decoded stream (which should be equal
 * to 'length'). Note that the output buffer must be allocated by the
 * caller.  If 'max_input_length' is not null, then it specifies the
 * number of encoded bytes that should be at most read from the input
 * buffer. In that case the 'length' parameter is ignored. This
 * enables the caller to decode a stream without actually knowing how
 * much decoded data to expect (of course, the buffer must be large
 * enough).
 */
size_t KwBase64_Decode(const unsigned char *input,
                                      size_t length,
                                      unsigned char *output,
                                      size_t max_input_length);

#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif
