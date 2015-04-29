#ifndef GETOPT_INTERNAL_H
#define GETOPT_INTERNAL_H
#define no_argument       0
#define required_argument 1
#define OPTIONAL_ARG      2

#ifdef UNICODE
#define _toptarg woptarg
#define _toptind woptind
#define _topterr wopterr
#define _toptopt woptopt
#define _tgetopt wgetopt
#define _tgetopt_long wgetopt_long
#define _tgetopt_long_only wgetopt_long_only
#define _TOptionTags woptionTag
#define _toption woption
#elif defined(_MBCS)
#define _toptarg optarg
#define _toptind optind
#define _topterr opterr
#define _toptopt optopt
#define _tgetopt getopt
#define _tgetopt_long getopt_long
#define _tgetopt_long_only getopt_long_only
#define _toption option
#define _TOptionTags _optionTag
#endif

typedef struct _TOptionTags
{
  const TCHAR *name;             /* the name of the long option */
  int has_arg;                  /* one of the above macros */
  int *flag;                    /* determines if getopt_long() returns a
                                 * value for a long option; if it is
                                 * non-NULL, 0 is returned as a function
                                 * value and the value of val is stored in
                                 * the area pointed to by flag.  Otherwise,
                                 * val is returned. */
  int val;                      /* determines the value to return if flag is
                                 * NULL. */
} _toption;


extern TCHAR *_toptarg;
extern int _toptind;
extern int _topterr;
extern int _toptopt;

int _tgetopt(int argc, TCHAR **argv, TCHAR *optstring);
int _tgetopt_long (int argc, TCHAR **argv, const TCHAR *shortopts,
                   const _toption * longopts, int *longind);
int _tgetopt_long_only (int argc, TCHAR **argv, const TCHAR *shortopts,
                        const _toption * longopts, int *longind);

#endif
