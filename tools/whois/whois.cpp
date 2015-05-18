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
#include <string>
#include <codecvt>
#include <vector>
#pragma comment(lib,"ws2_32")


static wchar_t whoisList[] =L"whois.internic.net";
wchar_t *host = nullptr;
wchar_t other[2048] = { 0 };
int optset = 0;

static bool Whois(const wchar_t *domian);
static void usage()
{
    printf("usage: whois [-h hostname] name ....\n");
}

bool StringToWideString(const std::string& src, std::wstring &wstr)
{
    std::locale sys_locale("");
    const char* data_from = src.c_str();
    const char* data_from_end = src.c_str() + src.size();
    const char* data_from_next = 0;

    wchar_t* data_to = new wchar_t[src.size() + 1];
    wchar_t* data_to_end = data_to + src.size() + 1;
    wchar_t* data_to_next = 0;

    wmemset(data_to, 0, src.size() + 1);

    typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
    mbstate_t in_state = { 0 };
    auto result = std::use_facet<convert_facet>(sys_locale).in(
        in_state, data_from, data_from_end, data_from_next,
        data_to, data_to_end, data_to_next);
    if (result == convert_facet::ok)
    {
        wstr = data_to;
        delete[] data_to;
        return true;
    }
    delete[] data_to;
    return false;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage();
        return 0;
    }
    host = whoisList;
    std::vector<std::string> domainV;
    for (int i = 1; i < argc; i++){
        switch (argv[i][0]){
        case '-':
        case '/':
            if (strlen(argv[i]) < 2)break;
            if (strcmp(&argv[i][1], "h") == 0){
                if (i + 2 < argc)
                {
                    std::string str = argv[i + 1];
                    std::wstring wstr;
                    if (!StringToWideString(str, wstr))
                        return 1;
                    wcsncpy_s(other, wstr.c_str(), 2048);
                    host = other;
                    i++;
                }
            }
            break;
        default:
            domainV.push_back(argv[i]);
            break;
        }
    }
    char ch;
    DWORD dwRetval;
    ADDRINFOW *result = NULL;
    ADDRINFOW hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    WSADATA wsaData;
    auto iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if ((dwRetval = GetAddrInfoW(host, nullptr, &hints, &result)) != 0){
        wprintf(L"whois: GetAddrInfoW failed with error: %d\n", dwRetval);
        WSACleanup();
        return 1;
    }
    if (result == nullptr)
        return 1;
    SOCKET sock;
    sock = socket(result->ai_family, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        FreeAddrInfoW(result);
        WSACleanup();
        return 1;
    }
    wchar_t ipstringbuffer[46];
    DWORD ipbufferlength = 46;
    WSAAddressToString(result->ai_addr, (DWORD)result->ai_addrlen, NULL,
        ipstringbuffer, &ipbufferlength);
    sockaddr_in sin;
    memset(/*(caddr_t)*/&sin, 0, sizeof(sin));
    sin.sin_family = result->ai_family;
    ULONG iaddr;
    InetPtonW(result->ai_family, ipstringbuffer, &iaddr);
    sin.sin_addr.s_addr = iaddr;
    sin.sin_port = htons(43);
    iResult = connect(sock, (sockaddr *)&sin, sizeof(sin));
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
        iResult = closesocket(sock);
        if (iResult == SOCKET_ERROR)
            wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        FreeAddrInfoW(result);
        WSACleanup();
        return 1;
    }
    auto i = domainV.size();
    while (i-- > 1){
        auto dm = domainV[i-1];
        send(sock, dm.c_str(), dm.size(), 0);
        send(sock, " ", 1, 0);
    }
    send(sock, domainV[0].c_str(), domainV[0].size(), 0);
    send(sock, "\r\n", 2, 0);
    wprintf(L"[%s]\n", host);
    while (recv(sock, &ch, 1, 0) == 1)
        putchar(ch);
    FreeAddrInfoW(result);
    WSACleanup();
    return 0;
}
