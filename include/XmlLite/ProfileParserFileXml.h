/*
*
*/

#ifndef PHO_XML_PROFIEPARSER_H
#define PHO_XML_PROFILEPARSER_H

#include <Windows.h>
#include <string>
#include <map>

#ifndef __cplusplus
#error "Only Support C++"
#endif

namespace Profile {
class ProfileParserBaseXml {
private:
  std::map<std::wstring, std::wstring> kvmap;
  std::wstring configfile;
  bool BeWriteAndSave();
  bool BeLoadAndRead();
  bool beFaild;
public:
  ProfileParserBaseXml(std::wstring profile);
  ProfileParserBaseXml() {
    wchar_t szPath[30276] = {0};
    /////nullptr
    GetModuleFileNameW(nullptr, szPath, 30276);
    wcscat_s(szPath, L".config");
    ProfileParserBaseXml(std::wstring(szPath));
  }
  std::wstring Get(std::wstring key);
  std::string Get(std::string key);
  std::string Get(const char *key);
  bool Set(std::wstring key, std::wstring value);
  bool Set(std::string key, std::string value);
  bool CreateNewConfig(std::wstring filename);
  bool OpenOtherConfig(std::wstring configpath);
  bool IsParserFaild(){return beFaild;};
};

typedef ProfileParserBaseXml ConfiguretionManager;
}

#endif
