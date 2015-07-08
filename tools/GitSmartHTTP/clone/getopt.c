/*
* getopt  Unicode
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "getopt.h"

#define w(x) L##x
/* macros */

/* types */
typedef enum GETOPT_ORDERING_W
{
  PERMUTE,
  RETURN_IN_ORDER,
  REQUIRE_ORDER
} GETOPT_ORDERING_W;

/* globally-defined variables */
wchar_t *woptarg = NULL;
int woptind = 0;
int wopterr = 1;
int woptopt = '?';

/* functions */

/* reverse_argv_elements:  reverses num elements starting at argv */
static void
reverse_argv_elements (wchar_t **argv, int num)
{
  int i;
  wchar_t *tmp;

  for (i = 0; i < (num >> 1); i++)
    {
      tmp = argv[i];
      argv[i] = argv[num - i - 1];
      argv[num - i - 1] = tmp;
    }
}

/* permute: swap two blocks of argv-elements given their lengths */
static void
permute (wchar_t **argv, int len1, int len2)
{
  reverse_argv_elements (argv, len1);
  reverse_argv_elements (argv, len1 + len2);
  reverse_argv_elements (argv, len2);
}

/* is_option: is this argv-element an option or the end of the option list? */
static int
is_option (wchar_t *argv_element, int only)
{
  return ((argv_element == NULL)
          || (argv_element[0] == _T('-')) || (only && argv_element[0] == _T('+')));
}

/* getopt_internal:  the function that does all the dirty work */
static int
getopt_internal (int argc, wchar_t **argv, wchar_t *shortopts,
                 woption * longopts, int *longind, int only)
{
  GETOPT_ORDERING_W ordering = PERMUTE;
  static size_t optwhere = 0;
  size_t permute_from = 0;
  int num_nonopts = 0;
  int optindex = 0;
  size_t match_chars = 0;
  wchar_t *possible_arg = NULL;
  int longopt_match = -1;
  int has_arg = -1;
  wchar_t *cp = NULL;
  int arg_next = 0;

  /* first, deal with silly parameters and easy stuff */
  if (argc == 0 || argv == NULL || (shortopts == NULL && longopts == NULL))
    return (woptopt = '?');
  if (woptind >= argc || argv[woptind] == NULL)
    return EOF;
  if (wcscmp (argv[woptind], L"--" )== 0)
    {
      woptind++;
      return EOF;
    }
  /* if this is our first time through */
  if (woptind == 0)
    woptind = optwhere = 1;

  /* define ordering */
  if (shortopts != NULL && (*shortopts == '-'|| *shortopts == '+'))
    {
      ordering = (*shortopts ==  '-') ? RETURN_IN_ORDER : REQUIRE_ORDER;
      shortopts++;
    }
  //else
    //ordering = (_wgetenv (L"POSIXLY_CORRECT") != NULL) ? REQUIRE_ORDER : PERMUTE;

  /*
   * based on ordering, find our next option, if we're at the beginning of
   * one
   */
  if (optwhere == 1)
    {
      switch (ordering)
        {
        case PERMUTE:
          permute_from = woptind;
          num_nonopts = 0;
          while (!is_option (argv[woptind], only))
            {
              woptind++;
              num_nonopts++;
            }
          if (argv[woptind] == NULL)
            {
              /* no more options */
              woptind = permute_from;
              return EOF;
            }
          else if (wcscmp (argv[woptind], L"--") == 0)
            {
              /* no more options, but have to get `--' out of the way */
              permute (argv + permute_from, num_nonopts, 1);
              woptind = permute_from + 1;
              return EOF;
            }
          break;
        case RETURN_IN_ORDER:
          if (!is_option (argv[woptind], only))
            {
              woptarg = argv[woptind++];
              return (woptopt = 1);
            }
          break;
        case REQUIRE_ORDER:
          if (!is_option (argv[woptind], only))
            return EOF;
          break;
        }
    }
  /* we've got an option, so parse it */

  /* first, is it a long option? */
  if (longopts != NULL
      && (memcmp (argv[woptind], L"--", 2) == 0
          || (only && argv[woptind][0] == '+')) && optwhere == 1)
    {
      /* handle long options */
      if (memcmp (argv[woptind], L"--", 2) == 0)
        optwhere = 2;
      longopt_match = -1;
      possible_arg = wcschr (argv[woptind] + optwhere,  '=');
      if (possible_arg == NULL)
        {
          /* no =, so next argv might be arg */
          match_chars = wcslen (argv[woptind]);
          possible_arg = argv[woptind] + match_chars;
          match_chars = match_chars - optwhere;
        }
      else
        match_chars = (possible_arg - argv[woptind]) - optwhere;
      for (optindex = 0; longopts[optindex].name != NULL; optindex++)
        {
          if (memcmp (argv[woptind] + optwhere,
                      longopts[optindex].name, match_chars) == 0)
            {
              /* do we have an exact match? */
              if (match_chars == wcslen (longopts[optindex].name))
                {
                  longopt_match = optindex;
                  break;
                }
              /* do any characters match? */
              else
                {
                  if (longopt_match < 0)
                    longopt_match = optindex;
                  else
                    {
                      /* we have ambiguous options */
                      if (wopterr)
                        fwprintf (stderr, L"%s: option `%s' is ambiguous "
                                 L"(could be `--%s' or `--%s')\n",
                                 argv[0],
                                 argv[woptind],
                                 longopts[longopt_match].name,
                                 longopts[optindex].name);
                      return (woptopt = '?');
                    }
                }
            }
        }
      if (longopt_match >= 0)
        has_arg = longopts[longopt_match].has_arg;
    }
  /* if we didn't find a long option, is it a short option? */
  if (longopt_match < 0 && shortopts != NULL)
    {
      cp = wcschr (shortopts, argv[woptind][optwhere]);
      if (cp == NULL)
        {
          /* couldn't find option in shortopts */
          if (wopterr)
            fwprintf (stderr,
                     L"%s: invalid option -- `-%c'\n",
                     argv[0], argv[woptind][optwhere]);
          optwhere++;
          if (argv[woptind][optwhere] ==  '\0')
            {
              woptind++;
              optwhere = 1;
            }
          return (woptopt = '?');
        }
      has_arg = ((cp[1] ==  ':')
                 ? ((cp[2] ==  ':') ? OPTIONAL_ARG : required_argument) : no_argument);
      possible_arg = argv[woptind] + optwhere + 1;
      woptopt = *cp;
    }
  /* get argument and reset optwhere */
  arg_next = 0;
  switch (has_arg)
    {
    case OPTIONAL_ARG:
      if (*possible_arg ==  '=')
        possible_arg++;
      if (*possible_arg !=  '\0')
        {
          woptarg = possible_arg;
          optwhere = 1;
        }
      else
        woptarg = NULL;
      break;
    case required_argument:
      if (*possible_arg ==  '=')
        possible_arg++;
      if (*possible_arg !=  '\0')
        {
          woptarg = possible_arg;
          optwhere = 1;
        }
      else if (woptind + 1 >= argc)
        {
          if (wopterr)
            {
              fwprintf (stderr, L"%s: argument required for option `", argv[0]);
              if (longopt_match >= 0)
                fwprintf (stderr, L"--%s'\n", longopts[longopt_match].name);
              else
                fwprintf (stderr, L"-%c'\n", *cp);
            }
          woptind++;
          return (woptopt = ':');
        }
      else
        {
          woptarg = argv[woptind + 1];
          arg_next = 1;
          optwhere = 1;
        }
      break;
    case no_argument:
      if (longopt_match < 0)
        {
          optwhere++;
          if (argv[woptind][optwhere] ==  w('\0'))
            optwhere = 1;
        }
      else
        optwhere = 1;
      woptarg = NULL;
      break;
    }

  /* do we have to permute or otherwise modify woptind? */
  if (ordering == PERMUTE && optwhere == 1 && num_nonopts != 0)
    {
      permute (argv + permute_from, num_nonopts, 1 + arg_next);
      woptind = permute_from + 1 + arg_next;
    }
  else if (optwhere == 1)
    woptind = woptind + 1 + arg_next;

  /* finally return */
  if (longopt_match >= 0)
    {
      if (longind != NULL)
        *longind = longopt_match;
      if (longopts[longopt_match].flag != NULL)
        {
          *(longopts[longopt_match].flag) = longopts[longopt_match].val;
          return 0;
        }
      else
        return longopts[longopt_match].val;
    }
  else
    return woptopt;
}


int
wgetopt (int argc, wchar_t **argv, wchar_t *optstring)
{
  return getopt_internal (argc, argv, optstring, NULL, NULL, 0);
}

int
wgetopt_long (int argc, wchar_t **argv, const wchar_t *shortopts,
             const woption * longopts, int *longind)
{
  return getopt_internal (argc, argv, (wchar_t *)shortopts, (woption*)longopts, longind, 0);
}

int
wgetopt_long_only (int argc, wchar_t **argv, const wchar_t *shortopts,
                  const woption * longopts, int *longind)
{
  return getopt_internal (argc, argv, (wchar_t *)shortopts, (woption*)longopts, longind, 1);
}

/* end of file GETOPT.C */
