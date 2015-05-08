#ifndef __GETOPT_H_
#define __GETOPT_H_

enum _getopt_arg
{
    null_argument     = 0,
    no_argument       = 0,
    required_argument = 1,
    optional_argument = 2
};

#include <string.h>
#include <wchar.h>

int       optind = 1;
int       opterr = 1;
int       optopt = '?';
wchar_t * optarg;

// Unicode
struct option
{
    const wchar_t * name;
    int             has_arg;
    int           * flag;
    wchar_t         val;
};

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

enum ENUM_ORDERING
{
    REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
};

static struct _getopt_data
{
    int                optind;
    int                opterr;
    int                optopt;
    wchar_t          * optarg;
    int                __initialized;
    wchar_t          * __nextchar;
    enum ENUM_ORDERING __ordering;
    int                __posixly_correct;
    int                __first_nonopt;
    int                __last_nonopt;
} getopt_data;

static void _getopt_exchange(wchar_t ** argv, struct _getopt_data * d)
{
    int bottom = d->__first_nonopt;
    int middle = d->__last_nonopt;
    int top = d->optind;
    wchar_t *tem;
    while (top > middle && middle > bottom)
    {
        if (top - middle > middle - bottom)
        {
            int len = middle - bottom;
            register int i;
            for (i = 0; i < len; i++)
            {
                tem = argv[bottom + i];
                argv[bottom + i] = argv[top - (middle - bottom) + i];
                argv[top - (middle - bottom) + i] = tem;
            }
            top -= len;
        }
        else
        {
            int len = top - middle;
            register int i;
            for (i = 0; i < len; i++)
            {
                tem = argv[bottom + i];
                argv[bottom + i] = argv[middle + i];
                argv[middle + i] = tem;
            }
            bottom += len;
        }
    }
    d->__first_nonopt += (d->optind - d->__last_nonopt);
    d->__last_nonopt = d->optind;
}

static const wchar_t * _getopt_initialize(wchar_t const * optstring, struct _getopt_data * d, int posixly_correct)
{
    d->__first_nonopt = d->__last_nonopt = d->optind;
    d->__nextchar = NULL;
    d->__posixly_correct = posixly_correct | !!_wgetenv(L"POSIXLY_CORRECT");
    if (optstring[0] == L'-')
    {
        d->__ordering = RETURN_IN_ORDER;
        ++optstring;
    }
    else if (optstring[0] == L'+')
    {
        d->__ordering = REQUIRE_ORDER;
        ++optstring;
    }
    else if (d->__posixly_correct)
        d->__ordering = REQUIRE_ORDER;
    else
        d->__ordering = PERMUTE;
    return optstring;
}

static int _getopt_internal_r(int argc, wchar_t * const * argv, wchar_t const * optstring, struct option const * longopts, int * longind, int long_only, struct _getopt_data * d, int posixly_correct)
{
    int print_errors = d->opterr;
    if (argc < 1)
        return -1;
    d->optarg = NULL;
    if (d->optind == 0 || !d->__initialized)
    {
        if (d->optind == 0)
            d->optind = 1;
        optstring = _getopt_initialize(optstring, d, posixly_correct);
        d->__initialized = 1;
    }
    else if (optstring[0] == L'-' || optstring[0] == L'+')
        optstring++;
    if (optstring[0] == L':')
        print_errors = 0;
    if (d->__nextchar == NULL || *d->__nextchar == L'\0')
    {
        if (d->__last_nonopt > d->optind)
            d->__last_nonopt = d->optind;
        if (d->__first_nonopt > d->optind)
            d->__first_nonopt = d->optind;
        if (d->__ordering == PERMUTE)
        {
            if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optind)
                _getopt_exchange((wchar_t **)argv, d);
            else if (d->__last_nonopt != d->optind)
                d->__first_nonopt = d->optind;
            while (d->optind < argc && (argv[d->optind][0] != L'-' || argv[d->optind][1] == L'\0'))
                d->optind++;
            d->__last_nonopt = d->optind;
        }
        if (d->optind != argc && !wcscmp(argv[d->optind], L"--"))
        {
            d->optind++;
            if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optind)
                _getopt_exchange((wchar_t **)argv, d);
            else if (d->__first_nonopt == d->__last_nonopt)
                d->__first_nonopt = d->optind;
            d->__last_nonopt = argc;
            d->optind = argc;
        }
        if (d->optind == argc)
        {
            if (d->__first_nonopt != d->__last_nonopt)
                d->optind = d->__first_nonopt;
            return -1;
        }
        if ((argv[d->optind][0] != L'-' || argv[d->optind][1] == L'\0'))
        {
            if (d->__ordering == REQUIRE_ORDER)
                return -1;
            d->optarg = argv[d->optind++];
            return 1;
        }
        d->__nextchar = (argv[d->optind] + 1 + (longopts != NULL && argv[d->optind][1] == L'-'));
    }
    if (longopts != NULL && (argv[d->optind][1] == L'-' || (long_only && (argv[d->optind][2] || !wcschr(optstring, argv[d->optind][1])))))
    {
        wchar_t *nameend;
        unsigned int namelen;
        const struct option *p;
        const struct option *pfound = NULL;
        struct option_list
        {
            const struct option *p;
            struct option_list *next;
        } *ambig_list = NULL;
        int exact = 0;
        int indfound = -1;
        int option_index;
        for (nameend = d->__nextchar; *nameend && *nameend != L'='; nameend++);
        namelen = (unsigned int)(nameend - d->__nextchar);
        for (p = longopts, option_index = 0; p->name; p++, option_index++)
            if (!wcsncmp(p->name, d->__nextchar, namelen))
            {
            if (namelen == (unsigned int)wcslen(p->name))
            {
                pfound = p;
                indfound = option_index;
                exact = 1;
                break;
            }
            else if (pfound == NULL)
            {
                pfound = p;
                indfound = option_index;
            }
            else if (long_only || pfound->has_arg != p->has_arg || pfound->flag != p->flag || pfound->val != p->val)
            {
                struct option_list *newp = (struct option_list*)alloca(sizeof(*newp));
                newp->p = p;
                newp->next = ambig_list;
                ambig_list = newp;
            }
            }
        if (ambig_list != NULL && !exact)
        {
            if (print_errors)
            {
                struct option_list first;
                first.p = pfound;
                first.next = ambig_list;
                ambig_list = &first;
                fwprintf(stderr, L"%s: option '%s' is ambiguous; possibilities:", argv[0], argv[d->optind]);
                do
                {
                    fwprintf(stderr, L" '--%s'", ambig_list->p->name);
                    ambig_list = ambig_list->next;
                }
                while (ambig_list != NULL);
                fputwc(L'\n', stderr);
            }
            d->__nextchar += wcslen(d->__nextchar);
            d->optind++;
            d->optopt = 0;
            return L'?';
        }
        if (pfound != NULL)
        {
            option_index = indfound;
            d->optind++;
            if (*nameend)
            {
                if (pfound->has_arg)
                    d->optarg = nameend + 1;
                else
                {
                    if (print_errors)
                    {
                        if (argv[d->optind - 1][1] == L'-')
                        {
                            fwprintf(stderr, L"%s: option '--%s' doesn't allow an argument\n", argv[0], pfound->name);
                        }
                        else
                        {
                            fwprintf(stderr, L"%s: option '%c%s' doesn't allow an argument\n", argv[0], argv[d->optind - 1][0], pfound->name);
                        }
                    }
                    d->__nextchar += wcslen(d->__nextchar);
                    d->optopt = pfound->val;
                    return L'?';
                }
            }
            else if (pfound->has_arg == 1)
            {
                if (d->optind < argc)
                    d->optarg = argv[d->optind++];
                else
                {
                    if (print_errors)
                    {
                        fwprintf(stderr, L"%s: option '--%s' requires an argument\n", argv[0], pfound->name);
                    }
                    d->__nextchar += wcslen(d->__nextchar);
                    d->optopt = pfound->val;
                    return optstring[0] == L':' ? L':' : L'?';
                }
            }
            d->__nextchar += wcslen(d->__nextchar);
            if (longind != NULL)
                *longind = option_index;
            if (pfound->flag)
            {
                *(pfound->flag) = pfound->val;
                return 0;
            }
            return pfound->val;
        }
        if (!long_only || argv[d->optind][1] == L'-' || wcschr(optstring, *d->__nextchar) == NULL)
        {
            if (print_errors)
            {
                if (argv[d->optind][1] == L'-')
                {
                    fwprintf(stderr, L"%s: unrecognized option '--%s'\n", argv[0], d->__nextchar);
                }
                else
                {
                    fwprintf(stderr, L"%s: unrecognized option '%c%s'\n", argv[0], argv[d->optind][0], d->__nextchar);
                }
            }
            d->__nextchar = (wchar_t *)L"";
            d->optind++;
            d->optopt = 0;
            return L'?';
        }
    }
    {
        wchar_t c = *d->__nextchar++;
        wchar_t *temp = (wchar_t*)wcschr(optstring, c);
        if (*d->__nextchar == L'\0')
            ++d->optind;
        if (temp == NULL || c == L':' || c == L';')
        {
            if (print_errors)
            {
                fwprintf(stderr, L"%s: invalid option -- '%c'\n", argv[0], c);
            }
            d->optopt = c;
            return L'?';
        }
        if (temp[0] == L'W' && temp[1] == L';')
        {
            wchar_t *nameend;
            const struct option *p;
            const struct option *pfound = NULL;
            int exact = 0;
            int ambig = 0;
            int indfound = 0;
            int option_index;
            if (longopts == NULL)
                goto no_longs;
            if (*d->__nextchar != L'\0')
            {
                d->optarg = d->__nextchar;
                d->optind++;
            }
            else if (d->optind == argc)
            {
                if (print_errors)
                {
                    fwprintf(stderr, L"%s: option requires an argument -- '%c'\n", argv[0], c);
                }
                d->optopt = c;
                if (optstring[0] == L':')
                    c = L':';
                else
                    c = L'?';
                return c;
            }
            else
                d->optarg = argv[d->optind++];
            for (d->__nextchar = nameend = d->optarg; *nameend && *nameend != L'='; nameend++);
            for (p = longopts, option_index = 0; p->name; p++, option_index++)
                if (!wcsncmp(p->name, d->__nextchar, nameend - d->__nextchar))
                {
                if ((unsigned int)(nameend - d->__nextchar) == wcslen(p->name))
                {
                    pfound = p;
                    indfound = option_index;
                    exact = 1;
                    break;
                }
                else if (pfound == NULL)
                {
                    pfound = p;
                    indfound = option_index;
                }
                else if (long_only || pfound->has_arg != p->has_arg || pfound->flag != p->flag || pfound->val != p->val)
                    ambig = 1;
                }
            if (ambig && !exact)
            {
                if (print_errors)
                {
                    fwprintf(stderr, L"%s: option '-W %s' is ambiguous\n", argv[0], d->optarg);
                }
                d->__nextchar += wcslen(d->__nextchar);
                d->optind++;
                return L'?';
            }
            if (pfound != NULL)
            {
                option_index = indfound;
                if (*nameend)
                {
                    if (pfound->has_arg)
                        d->optarg = nameend + 1;
                    else
                    {
                        if (print_errors)
                        {
                            fwprintf(stderr, L"%s: option '-W %s' doesn't allow an argument\n", argv[0], pfound->name);
                        }
                        d->__nextchar += wcslen(d->__nextchar);
                        return L'?';
                    }
                }
                else if (pfound->has_arg == 1)
                {
                    if (d->optind < argc)
                        d->optarg = argv[d->optind++];
                    else
                    {
                        if (print_errors)
                        {
                            fwprintf(stderr, L"%s: option '-W %s' requires an argument\n", argv[0], pfound->name);
                        }
                        d->__nextchar += wcslen(d->__nextchar);
                        return optstring[0] == L':' ? L':' : L'?';
                    }
                }
                else
                    d->optarg = NULL;
                d->__nextchar += wcslen(d->__nextchar);
                if (longind != NULL)
                    *longind = option_index;
                if (pfound->flag)
                {
                    *(pfound->flag) = pfound->val;
                    return 0;
                }
                return pfound->val;
            }
        no_longs:
            d->__nextchar = NULL;
            return L'W';
        }
        if (temp[1] == L':')
        {
            if (temp[2] == L':')
            {
                if (*d->__nextchar != L'\0')
                {
                    d->optarg = d->__nextchar;
                    d->optind++;
                }
                else
                    d->optarg = NULL;
                d->__nextchar = NULL;
            }
            else
            {
                if (*d->__nextchar != L'\0')
                {
                    d->optarg = d->__nextchar;
                    d->optind++;
                }
                else if (d->optind == argc)
                {
                    if (print_errors)
                    {
                        fwprintf(stderr, L"%s: option requires an argument -- '%c'\n", argv[0], c);
                    }
                    d->optopt = c;
                    if (optstring[0] == L':')
                        c = L':';
                    else
                        c = L'?';
                }
                else
                    d->optarg = argv[d->optind++];
                d->__nextchar = NULL;
            }
        }
        return c;
    }
}

static int _getopt_internal(int argc, wchar_t * const * argv, wchar_t const * optstring, struct option const * longopts, int * longind, int long_only, int posixly_correct)
{
    int result;
    getopt_data.optind = optind;
    getopt_data.opterr = opterr;
    result = _getopt_internal_r(argc, argv, optstring, longopts, longind, long_only, &getopt_data, posixly_correct);
    optind = getopt_data.optind;
    optarg = getopt_data.optarg;
    optopt = getopt_data.optopt;
    return result;
}

//static int getopt(int argc, wchar_t * const * argv, wchar_t const * optstring) throw()
//{
//    return _getopt_internal(argc, argv, optstring, (const struct option *) 0, (int *)0, 0, 0);
//}

//static int getopt_long(int argc, wchar_t * const * argv, wchar_t const * options, struct option const * long_options, int * opt_index) throw()
//{
//    return _getopt_internal(argc, argv, options, long_options, opt_index, 0, 0);
//}

static int getopt_long_only(int argc, wchar_t * const * argv, wchar_t const * options, struct option const * long_options, int * opt_index) throw()
{
    return _getopt_internal(argc, argv, options, long_options, opt_index, 1, 0);
}

#endif  // __GETOPT_H_
