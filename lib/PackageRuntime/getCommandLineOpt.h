#pragma once

#if defined (_WIN32)
    #if defined(EXPORT_LIBLLDB)
        #define  LLDB_API __declspec(dllexport)
    #elif defined(IMPORT_LIBLLDB)
        #define  LLDB_API  __declspec(dllimport)
    #else
        #define LLDB_API
    #endif
#else // defined (_MSC_VER)
    #define LLDB_API
#endif


// from getopt.h
#define no_argument       0
#define required_argument 1
#define optional_argument 2

// option structure
struct option
{
    const char *name;
    // has_arg can't be an enum because some compilers complain about
    // type mismatches in all the code that assumes it is an int.
    int  has_arg;
    int *flag;
    int  val;
};

LLDB_API int getopt( int argc, char * const argv[], const char *optstring );

// from getopt.h
extern LLDB_API char * optarg;
extern LLDB_API int    optind;
extern int    opterr;
extern int    optopt;

// defined in unistd.h
extern LLDB_API int    optreset;

LLDB_API int getopt_long
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);

LLDB_API int getopt_long_only
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);
