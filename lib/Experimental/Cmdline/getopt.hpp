
#ifndef GETOPT_HPP
#define GETOPT_HPP
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

int getopt( int argc, char * const argv[], const char *optstring );

// from getopt.h
extern char * optarg;
extern int    optind;
extern int    opterr;
extern int    optopt;

// defined in unistd.h
extern int    optreset;

int getopt_long
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);

int getopt_long_only
(
    int argc,
    char * const *argv,
    const char *optstring,
    const struct option *longopts,
    int *longindex
);

//////////////////////////////////////////////////
// option structure
struct woption
{
    const wchar_t *name;
    // has_arg can't be an enum because some compilers complain about
    // type mismatches in all the code that assumes it is an int.
    int  has_arg;
    int *flag;
    int  val;
};

int wgetopt( int argc, wchar_t * const argv[], const wchar_t *optstring );

// from getopt.h
extern wchar_t * optarg;
extern int    optind;
extern int    opterr;
extern int    optopt;

// defined in unistd.h
extern int    optreset;

int wgetopt_long
(
    int argc,
    wchar_t * const *argv,
    const wchar_t *optstring,
    const struct option *longopts,
    int *longindex
);

int wgetopt_long_only
(
    int argc,
    wchar_t * const *argv,
    const wchar_t *optstring,
    const struct woption *longopts,
    int *longindex
);

#if defined(UNICODE)||defined(_UNICODE)
#define _toptarg woptarg
#define _toptind woptind
#define _topterr wopterr
#define _toptopt woptopt
#define _tgetopt wgetopt
#define _tgetopt_long wgetopt_long
#define _tgetopt_long_only wgetopt_long_only
#define _toption woption

#else
#define _toptarg optarg
#define _toptind optind
#define _topterr opterr
#define _toptopt optopt
#define _tgetopt getopt
#define _tgetopt_long getopt_long
#define _tgetopt_long_only getopt_long_only
#define _toption option
#endif

#endif
