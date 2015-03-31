//===-- UriParser.cpp -------------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "UriParser.h"

// C Includes
#include <cstdlib>
#include <cstdint>

// C++ Includes
// Other libraries and framework includes
// Project includes

uint32_t
ToUInt32 (const char *s, uint32_t fail_value, int base, bool *success_ptr)
{
    if (s && s[0])
    {
        char *end = nullptr;
        const unsigned long uval = ::strtoul (s, &end, base);
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
UriParser::Parse(const char* uri,
    std::string& scheme,
    std::string& hostname,
    int& port,
    std::string& path
    )
{
    char scheme_buf[100] = {0};
    char hostname_buf[256] = {0};
    char port_buf[11] = {0}; // 10==strlen(2^32)
    char path_buf[2049] = {'/', 0};

    bool ok = false;
         if (4==sscanf(uri, "%99[^:/]://%255[^/:]:%10[^/]/%2047s", scheme_buf, hostname_buf, port_buf, path_buf+1)) { ok = true; }
    else if (3==sscanf(uri, "%99[^:/]://%255[^/:]:%10[^/]", scheme_buf, hostname_buf, port_buf)) { ok = true; }
    else if (3==sscanf(uri, "%99[^:/]://%255[^/]/%2047s", scheme_buf, hostname_buf, path_buf+1)) { ok = true; }
    else if (2==sscanf(uri, "%99[^:/]://%255[^/]", scheme_buf, hostname_buf)) { ok = true; }

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

