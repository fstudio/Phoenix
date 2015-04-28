/*********************************************************************************************************
*   Phoneix Xml Base Profile  Features
*   Note: ProfileManager.h
*   Date: 2015.01.06
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/

#ifndef PHO_XML_PROFIEPARSER_H
#define PHO_XML_PROFILEPARSER_H

#include <Windows.h>
#include <string>
#include <unordered_map>

#ifndef __cplusplus
#error "Only Support C++"
#endif

namespace Force {
class ProfileStructure;
class ProfileManager {
public:
  enum PROFILE_TYPE{
    XML_CONFIGFILE=0,
    INI_CONFIGFILE,
    JSON_CONFIGFILE
  };
private:
  std::unordered_map<std::wstring,std::wstring> kv;
  int filetype;
  std::wstring configFile;
public:
  ProfileManager(std::wstring profile);
  ProfileManager();
  ~ProfileManager();
  bool BeginParse();
  bool ChooseProfileType(int type=XML_CONFIGFILE);
  int get(const wchar_t *key,int de);
  std::wstring get(const wchar_t *key,const wchar_t *value);
  bool set(const wchar_t *key,int value);
  bool set(const wchar_t *key,const wchar_t *value);
};

typedef ProfileManager ConfiguretionManager;
}

#endif
