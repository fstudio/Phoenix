/*********************************************************************************************************
* whois.cpp
* Note: Phoenix whois tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef UNICODE
#define UNICODE
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

static wchar_t NICHOST[]=L"whois.internic.net";

class Whois{
private:
    wchar_t *host;
    int optset=0;
public:
    void usage();
};

int wmain(int argc,wchar_t **argv)
{
    return 0;
}
