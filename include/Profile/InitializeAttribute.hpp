/*********************************************************************************************************
* InitializeAttribute.hpp
* Note: Phoenix InitializeFile NT Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef INITIALIZEATTRIBUTE_HPP
#define INITIALIZEATTRIBUTE_HPP

#ifndef _WIN32
//#error "Only Support Windows System"
#endif
#include <cstdint>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>


#define ANONYMOUSSEC L"#anonymous"



/*
Determines whether a character is either an alphabetical or a numeric character. This determination is based on the semantics of the language selected by the user during setup or through Control Panel.

BOOL WINAPI IsCharAlphaNumeric(
  _In_  TCHAR ch
);

*/
class InitializeStructure {
private:
  bool isChanged;
  bool isCRLF;

public:
  struct Parameters {
    std::wstring key;
    std::wstring value;
    std::wstring comments;
    int nOrder;
    Parameters(std::wstring k, std::wstring v, std::wstring c, int nOrder = 0)
        : key(k), value(v), comments(c), nOrder(nOrder) {} ///////
    Parameters() {}
  };
  struct IniSection {
    typedef std::vector<Parameters>::iterator iterator;
    iterator begin() { return items.begin(); }
    iterator end() { return items.end(); }
    std::wstring comment;
    std::vector<Parameters> items;
  };
  /////////////////////////////////////////////////////////////////////
  std::unordered_map<std::wstring, IniSection *> attrTable;
  ////////////////////////////////////////////////////////////////////
  bool DeleteSection(const wchar_t *sec);
  bool DeleteParameters(const wchar_t *sec, const wchar_t *key, int Order = 0);
  void Clear() {
    for (auto &i : attrTable) {
      if (i.second)
        delete i.second;
    }
    attrTable.clear();
  }
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  InitializeStructure() : isChanged(false) {}
  ~InitializeStructure() {
    for (auto &i : attrTable) {
      if (i.second)
        delete i.second;
    }
    attrTable.clear();
  }
  std::wstring get(const wchar_t *sec, const wchar_t *key,const wchar_t *preset, int Order = 0);
  bool set(const wchar_t *sec, const wchar_t *key, const wchar_t *value,int Order = 0);
  bool InsertNewSection(const wchar_t *sec);
  bool IsChanged() { return this->isChanged; }
  ////Debug Method; sava file not used it
  std::wstring Print();
  bool InitializeFileAnalysis(wchar_t *buffer,size_t size);
  bool InitializeFileAnalysisEx(wchar_t *buffer,size_t size);
};

class InitializeAttribute {
private:
  std::wstring mfile;
  bool isEffective;
  bool isUpdate;
  int64_t lastTime;
  bool isParseOK;
  bool mReadOnly;
  bool GetFileAttributesZues(int64_t *now=nullptr);
  bool EffectiveAutoChecker();
  bool LoadData();
public:
  InitializeStructure iniStructure;
  InitializeAttribute &operator=(const InitializeAttribute &rhs) {
    /// value=value
    mfile=rhs.mfile;
    isEffective=rhs.isEffective;
    return *this;
  }
  InitializeAttribute(const InitializeAttribute &iattr) { operator=(iattr); }
  InitializeAttribute(const wchar_t *filePath,bool isReadOnly=false) : mfile(filePath),isEffective(false),isUpdate(false),isParseOK(false) ,mReadOnly(isReadOnly){
    if(EffectiveAutoChecker())
        isEffective=true;
    else{
        return ;
    }
    if(LoadData())
        isParseOK=true;
  }
  bool IsEffectiveFile(){return this->isEffective;}
  bool IsParseOK(){return this->isParseOK;}
  bool IsUpdated();
};

#endif
