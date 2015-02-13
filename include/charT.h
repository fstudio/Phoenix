//===============================Phoenix Char ================================
// char wchar_t
//
#ifndef PHOENIX_CHAR_BASE
#define PHOENIX_CHAR_BASE
#ifdef _WIN32
#include <tchar.h>
#else
#if defined(UNCIDOE) ||defined(_UNICODE)
#define TCHAR wchar_t
#define __T(x)  L(x)
#define _T(x) __T(x)
#else
#define TCHAR char
#define __T(x) x
#define _T(x) __T(x)
#endif

#endif
#endif
