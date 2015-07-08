#ifndef GETOPT_INTERNAL_H
#define GETOPT_INTERNAL_H
#define no_argument       0
#define required_argument 1
#define OPTIONAL_ARG      2


typedef struct woptionTag
{
  const wchar_t *name;             /* the name of the long option */
  int has_arg;                  /* one of the above macros */
  int *flag;                    /* determines if getopt_long() returns a
                                 * value for a long option; if it is
                                 * non-NULL, 0 is returned as a function
                                 * value and the value of val is stored in
                                 * the area pointed to by flag.  Otherwise,
                                 * val is returned. */
  int val;                      /* determines the value to return if flag is
                                 * NULL. */
} woption;


extern wchar_t *woptarg;
extern int woptind;
extern int wopterr;
extern int woptopt;

int wgetopt(int argc, wchar_t **argv, wchar_t *optstring);
int wgetopt_long (int argc, wchar_t **argv, const wchar_t *shortopts,
                   const woption * longopts, int *longind);
int wgetopt_long_only (int argc, wchar_t **argv, const wchar_t *shortopts,
                        const woption * longopts, int *longind);

#endif
