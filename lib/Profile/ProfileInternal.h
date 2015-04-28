/*********************************************************************************************************
*   Phoneix Profile  Features
*   Note: ProfileInternal.h
*   Data: 2015.01.17
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/


#ifndef PHOENIX_XMLLITE_H
#define PHOENIX_XMLLITE_H
#include <ole2.h>
#include <xmllite.h>
#include <stdio.h>
#include <shlwapi.h>
#include <unordered_map>
#include <string>

// "<applicationSettings>"

class JSONExcavator{
private:
    std::wstring fileDir;
public:
  JSONExcavator(std::wstring file):fileDir(file){}
  bool Reader(std::unordered_map<std::wstring,std::wstring> &kv);
  bool Writer(std::unordered_map<std::wstring,std::wstring> &kv);
};



#endif
