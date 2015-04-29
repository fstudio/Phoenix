
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include "getopt_internal.h"


/* macros */

/* types */
typedef enum GETOPT_ORDERING_T
{
  PERMUTE,
  RETURN_IN_ORDER,
  REQUIRE_ORDER
} GETOPT_ORDERING_T;

/* globally-defined variables */
TCHAR *_toptarg = NULL;
int _toptind = 0;
int _topterr = 1;
int _toptopt = _T('?');

/* functions */

/* reverse_argv_elements:  reverses num elements starting at argv */
static void
reverse_argv_elements (TCHAR **argv, int num)
{
  int i;
  TCHAR *tmp;

  for (i = 0; i < (num >> 1); i++)
    {
      tmp = argv[i];
      argv[i] = argv[num - i - 1];
      argv[num - i - 1] = tmp;
    }
}

/* permute: swap two blocks of argv-elements given their lengths */
static void
permute (TCHAR **argv, int len1, int len2)
{
  reverse_argv_elements (argv, len1);
  reverse_argv_elements (argv, len1 + len2);
  reverse_argv_elements (argv, len2);
}

/* is_option: is this argv-element an option or the end of the option list? */
static int
is_option (TCHAR *argv_element, int only)
{
  return ((argv_element == NULL)
          || (argv_element[0] == _T('-')) || (only && argv_element[0] == _T('+')));
}

/* getopt_internal:  the function that does all the dirty work */
static int
getopt_internal (int argc, TCHAR **argv, TCHAR *shortopts,
                 _toption * longopts, int *longind, int only)
{
  GETOPT_ORDERING_T ordering = PERMUTE;
  static size_t optwhere = 0;
  size_t permute_from = 0;
  int num_nonopts = 0;
  int optindex = 0;
  size_t match_chars = 0;
  TCHAR *possible_arg = NULL;
  int longopt_match = -1;
  int has_arg = -1;
  TCHAR *cp = NULL;
  int arg_next = 0;

  /* first, deal with silly parameters and easy stuff */
  if (argc == 0 || argv == NULL || (shortopts == NULL && longopts == NULL))
    return (_toptopt = _T('?'));
  if (_toptind >= argc || argv[_toptind] == NULL)
    return EOF;
  if (_tcscmp (argv[_toptind], _T("--") )== 0)
    {
      _toptind++;
      return EOF;
    }
  /* if this is our first time through */
  if (_toptind == 0)
    _toptind = optwhere = 1;

  /* define ordering */
  if (shortopts != NULL && (*shortopts == _T('-')|| *shortopts == _T('+')))
    {
      ordering = (*shortopts ==  _T('-')) ? RETURN_IN_ORDER : REQUIRE_ORDER;
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
          permute_from = _toptind;
          num_nonopts = 0;
          while (!is_option (argv[_toptind], only))
            {
              _toptind++;
              num_nonopts++;
            }
          if (argv[_toptind] == NULL)
            {
              /* no more options */
              _toptind = permute_from;
              return EOF;
            }
          else if (_tcscmp (argv[_toptind], _T("--")) == 0)
            {
              /* no more options, but have to get `--' out of the way */
              permute (argv + permute_from, num_nonopts, 1);
              _toptind = permute_from + 1;
              return EOF;
            }
          break;
        case RETURN_IN_ORDER:
          if (!is_option (argv[_toptind], only))
            {
              _toptarg = argv[_toptind++];
              return (_toptopt = 1);
            }
          break;
        case REQUIRE_ORDER:
          if (!is_option (argv[_toptind], only))
            return EOF;
          break;
        }
    }
  /* we've got an option, so parse it */

  /* first, is it a long option? */
  if (longopts != NULL
      && (memcmp (argv[_toptind], _T("--"), 2) == 0
          || (only && argv[_toptind][0] == _T('+'))) && optwhere == 1)
    {
      /* handle long options */
      if (memcmp (argv[_toptind], _T("--"), 2) == 0)
        optwhere = 2;
      longopt_match = -1;
      possible_arg = _tcschr (argv[_toptind] + optwhere,  _T('='));
      if (possible_arg == NULL)
        {
          /* no =, so next argv might be arg */
          match_chars = _tcslen (argv[_toptind]);
          possible_arg = argv[_toptind] + match_chars;
          match_chars = match_chars - optwhere;
        }
      else
        match_chars = (possible_arg - argv[_toptind]) - optwhere;
      for (optindex = 0; longopts[optindex].name != NULL; optindex++)
        {
          if (memcmp (argv[_toptind] + optwhere,
                      longopts[optindex].name, match_chars) == 0)
            {
              /* do we have an exact match? */
              if (match_chars == _tcslen (longopts[optindex].name))
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
                      if (_topterr)
                        _ftprintf (stderr, _T("%s: option `%s' is ambiguous "
                                 _T("(could be `--%s' or `--%s')\n")),
                                 argv[0],
                                 argv[_toptind],
                                 longopts[longopt_match].name,
                                 longopts[optindex].name);
                      return (_toptopt = _T('?'));
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
      cp = _tcschr (shortopts, argv[_toptind][optwhere]);
      if (cp == NULL)
        {
          /* couldn't find option in shortopts */
          if (_topterr)
            _ftprintf (stderr,
                     _T("%s: invalid option -- `-%c'\n"),
                     argv[0], argv[_toptind][optwhere]);
          optwhere++;
          if (argv[_toptind][optwhere] ==  _T('\0'))
            {
              _toptind++;
              optwhere = 1;
            }
          return (_toptopt = _T('?'));
        }
      has_arg = ((cp[1] ==  _T(':'))
                 ? ((cp[2] ==  _T(':')) ? OPTIONAL_ARG : required_argument) : no_argument);
      possible_arg = argv[_toptind] + optwhere + 1;
      _toptopt = *cp;
    }
  /* get argument and reset optwhere */
  arg_next = 0;
  switch (has_arg)
    {
    case OPTIONAL_ARG:
      if (*possible_arg ==  _T('='))
        possible_arg++;
      if (*possible_arg !=  _T('\0'))
        {
          _toptarg = possible_arg;
          optwhere = 1;
        }
      else
        _toptarg = NULL;
      break;
    case required_argument:
      if (*possible_arg ==  _T('='))
        possible_arg++;
      if (*possible_arg !=  _T('\0'))
        {
          _toptarg = possible_arg;
          optwhere = 1;
        }
      else if (_toptind + 1 >= argc)
        {
          if (_topterr)
            {
              _ftprintf (stderr, _T("%s: argument required for option `"), argv[0]);
              if (longopt_match >= 0)
                _ftprintf (stderr, _T("--%s'\n"), longopts[longopt_match].name);
              else
                _ftprintf (stderr, _T("-%c'\n"), *cp);
            }
          _toptind++;
          return (_toptopt =  _T(':'));
        }
      else
        {
          _toptarg = argv[_toptind + 1];
          arg_next = 1;
          optwhere = 1;
        }
      break;
    case no_argument:
      if (longopt_match < 0)
        {
          optwhere++;
          if (argv[_toptind][optwhere] ==  _T('\0'))
            optwhere = 1;
        }
      else
        optwhere = 1;
      _toptarg = NULL;
      break;
    }

  /* do we have to permute or otherwise modify _toptind? */
  if (ordering == PERMUTE && optwhere == 1 && num_nonopts != 0)
    {
      permute (argv + permute_from, num_nonopts, 1 + arg_next);
      _toptind = permute_from + 1 + arg_next;
    }
  else if (optwhere == 1)
    _toptind = _toptind + 1 + arg_next;

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
    return _toptopt;
}


int
_tgetopt (int argc, TCHAR **argv, TCHAR *optstring)
{
  return getopt_internal (argc, argv, optstring, NULL, NULL, 0);
}

int
_tgetopt_long (int argc, TCHAR **argv, const TCHAR *shortopts,
             const _toption * longopts, int *longind)
{
  return getopt_internal (argc, argv, (TCHAR *)shortopts, (_toption*)longopts, longind, 0);
}

int
_tgetopt_long_only (int argc, TCHAR **argv, const TCHAR *shortopts,
                  const _toption * longopts, int *longind)
{
  return getopt_internal (argc, argv, (TCHAR *)shortopts, (_toption*)longopts, longind, 1);
}

/* end of file GETOPT.C */
