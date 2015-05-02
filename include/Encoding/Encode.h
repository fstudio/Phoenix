/*********************************************************************************************************
*   Phoenix Encoding Convert
*   Note: Encode.h
*   Date: 2015.01.17
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHONEIX_ENCODING_ENCODE_H
#define PHONEIX_ENCODING_ENCODE_H

#ifdef __cplusplus
#include <string>
#ifdef _WIN32
///Defualt CodePage.
std::wstring MultiByteToUnicode(const std::string &str);
std::string UnicodeToMultiByte(const std::wstring &wstr);

////CodePage.
std::wstring MultiByteToUnicode(const std::string &str,unsigned cp);
std::string UnicodeToMultiByte(const std::wstring &wstr,unsigned cp);

///UTF-8
std::wstring UTF8ToUnicode(const std::string &str);
std::string UincodeToUTF8(const std::wstring &str);
#endif

#endif

typedef unsigned int UTF32;    /* at least 32 bits */
typedef unsigned short UTF16;  /* at least 16 bits */
typedef unsigned char UTF8;    /* typically 8 bits */
typedef unsigned char Boolean; /* 0 or 1 */

/* Some fundamental constants */
#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

#define UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4

#define UNI_UTF16_BYTE_ORDER_MARK_NATIVE 0xFEFF
#define UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

typedef enum {
  conversionOK,    /* conversion successful */
  sourceExhausted, /* partial character in source, but hit end */
  targetExhausted, /* insuff. room in target for conversion */
  sourceIllegal    /* source sequence is illegal/malformed */
} ConversionResult;

typedef enum { strictConversion = 0, lenientConversion } ConversionFlags;

/* This is for C++ and does no harm in C */
#ifdef __cplusplus
extern "C" {
#endif

ConversionResult ConvertUTF8toUTF16(const UTF8 **sourceStart,
                                    const UTF8 *sourceEnd, UTF16 **targetStart,
                                    UTF16 *targetEnd, ConversionFlags flags);

/**
 * Convert a partial UTF8 sequence to UTF32.  If the sequence ends in an
 * incomplete code unit sequence, returns \c sourceExhausted.
 */
ConversionResult ConvertUTF8toUTF32Partial(const UTF8 **sourceStart,
                                           const UTF8 *sourceEnd,
                                           UTF32 **targetStart,
                                           UTF32 *targetEnd,
                                           ConversionFlags flags);

/**
 * Convert a partial UTF8 sequence to UTF32.  If the sequence ends in an
 * incomplete code unit sequence, returns \c sourceIllegal.
 */
ConversionResult ConvertUTF8toUTF32(const UTF8 **sourceStart,
                                    const UTF8 *sourceEnd, UTF32 **targetStart,
                                    UTF32 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF8(const UTF16 **sourceStart,
                                    const UTF16 *sourceEnd, UTF8 **targetStart,
                                    UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF32toUTF8(const UTF32 **sourceStart,
                                    const UTF32 *sourceEnd, UTF8 **targetStart,
                                    UTF8 *targetEnd, ConversionFlags flags);

ConversionResult ConvertUTF16toUTF32(const UTF16 **sourceStart,
                                     const UTF16 *sourceEnd,
                                     UTF32 **targetStart, UTF32 *targetEnd,
                                     ConversionFlags flags);

ConversionResult ConvertUTF32toUTF16(const UTF32 **sourceStart,
                                     const UTF32 *sourceEnd,
                                     UTF16 **targetStart, UTF16 *targetEnd,
                                     ConversionFlags flags);

Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd);

unsigned getNumBytesForUTF8(UTF8 firstByte);

#ifdef __cplusplus
}
#endif

#endif
