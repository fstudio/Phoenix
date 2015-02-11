/*********************************************************************************************************
*   Phoneix Package Runtime Advanced unistd.h
*   Note: Some API
*   Data: 2015.02.11
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHONEIX_PACKAGE_RUNTIME_ADVANCED_UNISTD_H
#define PHONEIX_PACKAGE_RUNTIME_ADVANCED_UNISTD_H
#include "rtdefs.h"
///This file is enable dllimport
#define DLLIMPORT 1

#define no_argument       0
#define required_argument 1
#define optional_argument 2
struct option
{
    const char *name;
    // has_arg can't be an enum because some compilers complain about
    // type mismatches in all the code that assumes it is an int.
    int  has_arg;
    int *flag;
    int  val;
};


PKG_BEGIN_DECL

PKGEXTERN int getopt( int argc, char * const argv[], const char *optstring );

// from getopt.h
extern PKGEXTERN char * optarg;
extern PKGEXTERN int    optind;
extern int    opterr;
extern int    optopt;

// defined in unistd.h
extern PKGEXTERN int    optreset;

PKGEXTERN int getopt_long
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);

PKGEXTERN int getopt_long_only
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);

PKG_END_DECL


#endif
