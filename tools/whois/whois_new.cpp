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

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

static wchar_t* whoisList[]={
    L"whois.internic.net",
    L"whois.edu.cn",
    L"whois.cnnic.net.cn",
    L"whois.arin.net",
    L"whois.apnic.net",
    L"whois.ripe.ne",
    L"whois.twnic.net",
    L"whois.nic.ad.jp",
    L"whois.krnic.net",
    L"whois.lacnic.net"
};

static bool Whois(const wchar_t *domian);
static void usage()
{
    printf("usage: whois [-h hostname] name ....\n");
}

int wmain(int argc,wchar_t **argv)
{
    argc--;
    argv++;
    if(!argc){
        usage();
        return 0;
    }
    return 0;
}

static bool Whois(const wchar_t *domian){
    int iResult;
    INT iRetval;
    DWORD dwRetval;
    ADDRINFOW *result = NULL;
    ADDRINFOW *ptr = NULL;
    ADDRINFOW hints;
    ZeroMemory( &hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    WSADATA wsaData;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if((dwRetval=GetAddrInfoW(whoisList[0],nullptr,&hints,&result))!=0){
        wprintf(L"whois: GetAddrInfoW failed with error: %d\n", dwRetval);
        WSACleanup();
        return 1;
    }
    ////
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {
        switch (ptr->ai_family) {
            case AF_UNSPEC:
            wprintf(L"Unspecified\n");
            break;
            case AF_INET:
            break;
            case AF_INET6:
            break;
            default:
            wprintf(L"Other %ld\n", ptr->ai_family);
            break;
        }
    }
    //auto s=socket()
    return true;
}
