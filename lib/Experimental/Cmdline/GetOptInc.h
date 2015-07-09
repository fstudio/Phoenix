#pragma once
#define  _CRT_SECURE_NO_WARNINGS

#if defined (_MSC_VER)
    #if defined(EXPORT_LIBLLDB)
        #define  LLDB_API __declspec(dllexport)
    #elif defined(IMPORT_LIBLLDB)
        #define  LLDB_API __declspec(dllimport)
    #else
        #define LLDB_API
    #endif
#else // defined (_MSC_VER)
    #define LLDB_API
#endif

#if !defined(INT32_MAX)
    #define INT32_MAX 2147483647
#endif

#if !defined(UINT32_MAX)
    #define UINT32_MAX 4294967295U
#endif

#if !defined(UINT64_MAX)
    #define UINT64_MAX 18446744073709551615ULL
#endif

#include <tchar.h>

#ifdef UNICODE
#define optarg woptarg
#define optind woptind
#define opterr wopterr
#define optopt woptopt
#define getopt wgetopt
#define getopt_long wgetopt_long
#define getopt_long_only wgetopt_long_only
#define option woption
#define optreset woptreset
#endif

// from getopt.h
#define no_argument       0
#define required_argument 1
#define optional_argument 2

// option structure
struct option
{
    const TCHAR *name;
    // has_arg can't be an enum because some compilers complain about
    // type mismatches in all the code that assumes it is an int.
    int  has_arg;
    int *flag;
    int  val;
};

int getopt( int argc, TCHAR * const argv[], const TCHAR *optstring );

// from getopt.h
extern TCHAR * optarg;
extern int    optind;
extern int    opterr;
extern int    optopt;

// defined in unistd.h
extern int    optreset;

int getopt_long
(
    int argc,
    TCHAR * const *argv,
    const TCHAR *optstring,
    const struct option *longopts,
    int *longindex
);

int getopt_long_only
(
    int argc,
    TCHAR * const *argv,
    const TCHAR *optstring,
    const struct option *longopts,
    int *longindex
);
