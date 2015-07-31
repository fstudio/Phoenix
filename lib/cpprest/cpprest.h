/***/

#ifndef PHOENIX_HTTP_H
#define PHOENIX_HTTP_H

#include <comutil.h>
#include <windows.h>
#include <Winhttp.h>

#define DEFAULT_AGENT L"Hero/1.0.0.Simulator";


enum HTTPMethod{
    HttpVerbGET,
    HttpVerbPOST,
    HttpVerbPUT,
    HttpVerbDELETE,
    HttpVerbHEAD,
    HttpVerbOPTIONS,
    HttpVerbTRACE,
    HttpVerbCONNECT,
    HttpVerbMOVE,
    HttpVerbPROPFIND,
    HttpVerbPROPPATCH,
    HttpVerbMKCOL,
    HttpVerbLOCK,
    HttpVerbUNLOCK,
    HttpVerbSEARCH,
    HttpVerbUnknown
};

#endif
