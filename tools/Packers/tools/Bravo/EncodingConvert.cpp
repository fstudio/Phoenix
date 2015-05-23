/*********************************************************************************************************
*   Phoneix Plugin Native Launcher Host
*   Note: EncodingConvert.cpp
*   Date: 2015.05.23
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <string>


std::string UTF82ANSI(const char *szutf8)
{
    auto len=MultiByteToWideChar(CP_UTF8,0,szutf8,-1,NULL,0);
    wchar_t *buffer=new wchar_t[len+1];
    MultiByteToWideChar(CP_UTF8,0,(LPCSTR)szutf8,-1,buffer,len);
    len=WideCharToMultiByte(CP_ACP,0,buffer,-1,NULL,0,NULL,NULL);
    char *szgbk=new char[len+1];
    WideCharToMultiByte(CP_ACP,0,buffer,-1,szgbk,len,NULL,NULL);
    std::string str(szgbk);
    delete []buffer;
    delete []szgbk;
    return str;
}
