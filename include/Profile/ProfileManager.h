/*********************************************************************************************************
*   Phoneix Xml Base Profile  Features
*   Note: ProfileManager.h
*   Data: 2015.01.06
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/

#ifndef PHO_XML_PROFIEPARSER_H
#define PHO_XML_PROFILEPARSER_H

#include <Windows.h>
#include <string>
#include <map>

#ifndef __cplusplus
#error "Only Support C++"
#endif

namespace Profile {
class XmlIntegratedAnalyzer;
class ProfileManager {
private:
  XmlIntegratedAnalyzer *xiaptr;
  std::map<std::wstring, std::wstring> kvmap;
  std::map<std::wstring, std::wstring> appsettingkv;
  std::wstring configfile;
  bool BeWriteProfile();
  bool BeReadProfile();
  bool beFailed;

public:
  ProfileManager(std::wstring profile);
  ProfileManager();
  ~ProfileManager();
  std::wstring Get(std::wstring &key);
  std::wstring CharGet(const wchar_t *str);
  std::string CharGet(const char *str);
  std::string Get(std::string &key);
  // std::string Get(const char *key);
  bool Set(std::wstring &key, std::wstring &value);
  bool Set(std::string &key, std::string &value);
  bool CreateNewConfig(std::wstring &filename);
  bool OpenOtherConfig(std::wstring &configpath);
  bool IsParserFaild() { return beFailed; };
};

typedef ProfileManager ConfiguretionManager;
}

#endif
