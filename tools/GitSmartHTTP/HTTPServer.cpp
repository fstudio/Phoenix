/***/
#ifndef UNICODE
#define UNICODE
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <string>
#include <Http.h>
#pragma comment(lib,"Httpapi.lib")
//HttpCreateServerSession
#define U(x) L##x

static std::wstring HttpServerAPIKnownHeaders[] =
{
    U("Cache-Control"),
    U("Connection"),
    U("Data"),
    U("Keep-Alive"),
    U("Pragma"),
    U("Trailer"),
    U("Transfer-Encoding"),
    U("Upgrade"),
    U("Via"),
    U("Warning"),
    U("Allow"),
    U("Content-Length"),
    U("Content-Type"),
    U("Content-Encoding"),
    U("Content-Language"),
    U("Content-Location"),
    U("Content-Md5"),
    U("Content-Range"),
    U("Expires"),
    U("Last-Modified"),
    U("Accept"),
    U("Accept-Charset"),
    U("Accept-Encoding"),
    U("Accept-Language"),
    U("Authorization"),
    U("Cookie"),
    U("Expect"),
    U("From"),
    U("Host"),
    U("If-Match"),
    U("If-Modified-Since"),
    U("If-None-Match"),
    U("If-Range"),
    U("If-Unmodified-Since"),
    U("Max-Forwards"),
    U("Proxy-Authorization"),
    U("Referer"),
    U("Range"),
    U("Te"),
    U("Translate"),
    U("User-Agent"),
    U("Request-Maximum"),
    U("Accept-Ranges"),
    U("Age"),
    U("Etag"),
    U("Location"),
    U("Proxy-Authenticate"),
    U("Retry-After"),
    U("Server"),
    U("Set-Cookie"),
    U("Vary"),
    U("Www-Authenticate"),
    U("Response-Maximum")
};

