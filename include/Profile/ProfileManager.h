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
class XMLAnalyzer;
class ProfileStructure;
class ProfileManager {
private:
  XMLAnalyzer *xmlAnalyzer;
  ProfileStructure profileStructure;
public:
  ProfileManager(std::wstring profile);
  ProfileManager();
  ~ProfileManager();
};

typedef ProfileManager ConfiguretionManager;
}

#endif
