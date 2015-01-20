/*********************************************************************************************************
*   Phoneix XmlLite  Features
*   Note: ProfileManager.h
*   Data: 2015.01.06
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
class ProfileManager {
private:
  std::map<std::wstring, std::wstring> kvmap;
  std::map<std::wstring, std::wstring> appsettingkv;
  std::wstring configfile;
  bool BeWriteProfile();
  bool BeReadProfile();
  bool beFaild;
public:
  ProfileManager(std::wstring profile);
  ProfileManager() {
    wchar_t szPath[30276] = {0};
    /////nullptr
    GetModuleFileNameW(nullptr, szPath, 30276);
    wcscat_s(szPath, L".config");
    ProfileManager(std::wstring(szPath));
  }
  std::wstring Get(std::wstring &key);
  std::string Get(std::string &key);
  //std::string Get(const char *key);
  bool Set(std::wstring& key, std::wstring& value);
  bool Set(std::string& key, std::string& value);
  bool CreateNewConfig(std::wstring& filename);
  bool OpenOtherConfig(std::wstring& configpath);
  bool IsParserFaild(){return beFaild;};
};

typedef ProfileManager ConfiguretionManager;
}

#endif
