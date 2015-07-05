//===-- UriParser.cpp -------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include <string>
#include <cstdlib>
#include <cstdint>
#include <wchar.h>

typedef struct _schemes_t {
    /** The name of the scheme */
    const wchar_t *name;
    /** The default port for the scheme */
    unsigned default_port;
}schemes_t;

static schemes_t schemes[] =
{
    {L"http",     80},
    {L"ftp",      21},
    {L"https",    433},
    {L"git",     9418},
    {L"svn",      3690},
    {L"ssh",      22},
    { NULL, 0xFFFF }     /* unknown port */
};

int DefaultPort(const wchar_t * scheme)
{
    for(auto &s:schemes){
        if(wcscmp(scheme,s.name)==0)
            return s.default_port;
    }
    return 0;
}


uint32_t
ToUInt32 (const wchar_t *s, uint32_t fail_value, int base, bool *success_ptr)
{
    if (s && s[0])
    {
        wchar_t *end = nullptr;
        const unsigned long uval = ::wcstoul (s, &end, base);
        if (*end == '\0')
        {
            if (success_ptr)
                *success_ptr = (uval <= UINT32_MAX);
            return (uint32_t)uval; // All characters were used, return the result
        }
    }
    if (success_ptr) *success_ptr = false;
    return fail_value;
}


//----------------------------------------------------------------------
// UriParser::Parse
//----------------------------------------------------------------------
bool
URLParse(const wchar_t* uri,
    std::wstring& scheme,
    std::wstring& hostname,
    int& port,
    std::wstring& path
    )
{
    wchar_t scheme_buf[100] = {0};
    wchar_t hostname_buf[256] = {0};
    wchar_t port_buf[11] = {0}; // 10==strlen(2^32)
    wchar_t path_buf[2049] = {'/', 0};

    bool ok = false;
         if (4==swscanf(uri, L"%99[^:/]://%255[^/:]:%10[^/]/%2047s", scheme_buf, hostname_buf, port_buf, path_buf+1)) { ok = true; }
    else if (3==swscanf(uri, L"%99[^:/]://%255[^/:]:%10[^/]", scheme_buf, hostname_buf, port_buf)) { ok = true; }
    else if (3==swscanf(uri, L"%99[^:/]://%255[^/]/%2047s", scheme_buf, hostname_buf, path_buf+1)) { ok = true; }
    else if (2==swscanf(uri, L"%99[^:/]://%255[^/]", scheme_buf, hostname_buf)) { ok = true; }

    bool success = false;
    int port_tmp = -1;
    if (port_buf[0])
    {
        port_tmp = ToUInt32(port_buf, UINT32_MAX, 10, &success);
        if (!success || port_tmp > 65535)
        {
            // there are invalid characters in port_buf
            return false;
        }
    }
    if (ok)
    {
        scheme.assign(scheme_buf);
        hostname.assign(hostname_buf);
        port = port_tmp;
        path.assign(path_buf);
    }
    return ok;
}
