/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: Property.cpp
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <string>
#include <map>
#include <cassert>
#include "cpptoml.h"
#include "Header.hpp"

bool InitializeBravoEnvironment()
{
    std::string tomlSelf;
    char szBuf[MAX_PATH]={0};
    GetCurrentDirectoryA(szBuf,MAX_PATH);
    strcat(szBuf,"\\Bravo.toml");//current
    if(access(szBuf,04)==0)
    {
        tomlSelf=szBuf;
    }else{
        ///
    }
    ///1. current dir 2.package exe dir
    ///
    try{
        cpptoml::table g=cpptoml::parse_file(tomSelf.c_str());
    }catch(const cpptoml::parse_execption &e){
        std::cerr<<"Failed to parse"<<tomSelf<<":"<<e.what()<<std::endl;
        return false;
    }
    return true;
}


int ParserPropertyFormString(std::string text,std::map<std::string,std::string> &tb)
{
    if(text.empty())
        return -1;
    return 0;
}


