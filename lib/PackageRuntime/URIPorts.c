/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: URIPorts.c
*   Data: 2015.02.11
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/HTTP.h>
#include <string.h>

typedef struct _schemes_t {
    /** The name of the scheme */
    const char *name;
    /** The default port for the scheme */
    unsigned default_port;
}schemes_t;

static schemes_t schemes[] =
{
    {"http",     PKG_URI_HTTP_DEFAULT_PORT},
    {"ftp",      PKG_URI_FTP_DEFAULT_PORT},
    {"https",    PKG_URI_HTTPS_DEFAULT_PORT},
    {"imap",     PKG_URI_IMAP_DEFAULT_PORT},
    {"pop",      PKG_URI_POP_DEFAULT_PORT},
    {"telnet",   PKG_URI_TELNET_DEFAULT_PORT},
    {"ssh",      PKG_URI_SSH_DEFAULT_PORT},
    { NULL, 0xFFFF }     /* unknown port */
};

PKGEXTERN unsigned URIGetPortFromSchemes(const char *scheme_str)
{
    schemes_t *scheme;

    if (scheme_str) {
        for (scheme = schemes; scheme->name != NULL; ++scheme) {
            if (stricmp(scheme_str, scheme->name) == 0) {
                return scheme->default_port;
            }
        }
    }
    return 0;
}

