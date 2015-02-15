/*
* This Visual C Runtime Like getopt and wgetopt code
*/

#ifndef WIN32_GETOPT_H
#define WIN32_GETOPT_H

/* include files needed by this include file */

/* macros defined by this include file */
#define no_argument       0
#define required_argument 1
#define OPTIONAL_ARG 2

/* types defined by this include file */

/*Wide woption: The type of long woption */
typedef struct GETOPT_LONG_OPTION_TW
{
  const wchar_t *name;             /* the name of the long option */
  int has_arg;                  /* one of the above macros */
  int *flag;                       /* determines if getopt_long() returns a
                                    * value for a long option; if it is
                                    * non-NULL, 0 is returned as a function
                                    * value and the value of val is stored in
                                    * the area pointed to by flag.  Otherwise,
                                    * val is returned. */
  int val;                      /* determines the value to return if flag is
                                 * NULL. */
} woption;


/* ANIS option: The type of long option */
typedef struct GETOPT_LONG_OPTION_TA
{
  const char *name;             /* the name of the long option */
  int has_arg;                  /* one of the above macros */
  int *flag;                    /* determines if getopt_long() returns a
                                 * value for a long option; if it is
                                 * non-NULL, 0 is returned as a function
                                 * value and the value of val is stored in
                                 * the area pointed to by flag.  Otherwise,
                                 * val is returned. */
  int val;                      /* determines the value to return if flag is
                                 * NULL. */
} option;

#ifdef __cplusplus
extern "C"
{
#endif
  extern wchar_t *woptarg;
  extern int woptind;
  extern int wopterr;
  extern int woptopt;

  /* function prototypes */
  int wgetopt (int argc, wchar_t **argv, wchar_t *optstring);
  int wgetopt_long (int argc, wchar_t **argv, const wchar_t *shortopts,
    const woption * longopts, int *longind);
  int wgetopt_long_only (int argc, wchar_t **argv, const wchar_t *shortopts,
    const woption * longopts, int *longind);

  extern char *optarg;
  extern int optind;
  extern int opterr;
  extern int optopt;

  /* function prototypes */
  int getopt (int argc, char **argv, char *optstring);
  int getopt_long (int argc, char **argv, const char *shortopts,
    const option * longopts, int *longind);
  int getopt_long_only (int argc, char **argv, const char *shortopts,
    const option * longopts, int *longind);


#ifdef __cplusplus
};
#endif

/*
* TCHAR defined add
*/
#if defined(UNICODE)||defined(_UNICODE)
#define _toptarg woptarg
#define _toptind woptind
#define _topterr wopterr
#define _toptopt woptopt
#define _tgetopt wgetopt
#define _tgetopt_long wgetopt_long
#define _tgetopt_long_only wgetopt_long_only
#define _TOptionTags woptionTag
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
#define _TOptionTags _optionTag
#endif

#endif
