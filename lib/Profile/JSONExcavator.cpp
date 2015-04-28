/*********************************************************************************************************
*   Phoneix JSON Excavator
*   Note: JSONExcavator.cpp
*   Date: 2015.04.28
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/encodedstream.h>
#include <cstdio>


bool JSONExcavator::Reader(std::unordered_map<std::wstring,std::wstring> &kv)
{
    if (!PathFileExistsW(fileDir.c_str())) {
      return false;
    }
    FILE *fp;
    if(_wfopen_s(&fp,fileDir.c_str(),L"rb")!=0)
        return false;
    char buffer[65536]={0};
    FileReadStream bis(fp,buffer,sizeof(buffer));
    AutoUTFInputStream<unsigned,FileReadStream> eis(bis);
    Document d;
    d.ParseStream<0,AutoUTF<unsigned>>(eis);
    kv.clear();///when kv is be init and insert data.

    fclose(fp);
    return true;
}