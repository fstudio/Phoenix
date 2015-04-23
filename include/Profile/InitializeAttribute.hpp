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
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

#define ANONYMOUSSEC L"#anonymous"

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
  std::unordered_map<std::wstring, IniSection *> attrTable;
  bool DeleteSection(const wchar_t *sec) {
    auto it = attrTable.find(sec);
    if (it != attrTable.end()) {
      if (it->second) {
        delete it->second;
      }
      attrTable.erase(it);
      isChanged = true;
      return true;
    }
    return false;
  }
  bool DeleteParameters(const wchar_t *sec, const wchar_t *key, int Order = 0) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return false;
    auto iter = it->second->begin();
    auto end = it->second->end();
    auto index = 0;
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (index == Order) {
          it->second->items.erase(iter);
          isChanged = true;
          return true;
        }
        index++;
      }
      iter++;
    }
    return true;
  }
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
  std::wstring get(const wchar_t *sec, const wchar_t *key,
                   const wchar_t *preset, int Order = 0) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return preset;
    auto iter = it->second->begin();
    auto end = it->second->end();
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (Order == iter->nOrder) {
          return iter->value;
        }
      }
      iter++;
    }
    /// if(iter->second.)
    return preset;
  }
  bool set(const wchar_t *sec, const wchar_t *key, const wchar_t *value,
           int Order = 0) {
    const wchar_t *Ptr;
    if (!sec) {
      Ptr = ANONYMOUSSEC;
    } else {
      Ptr = sec;
    }
    auto it = attrTable.find(Ptr);
    if (it == attrTable.end() || !it->second)
      return false;
    auto iter = it->second->begin();
    auto end = it->second->end();
    bool bSet = false;
    while (iter != end) {
      if (iter->key.compare(key) == 0) ////Key ==key
      {
        if (Order == iter->nOrder) {
          iter->value = value;
          return true;
        }
        bSet = true;
      }
      iter++;
    }
    if (!bSet) {
      it->second->items.push_back(Parameters(key, value, std::wstring()));
    }
    /// if(iter->second.)
    return true;
  }
  bool InsertNewSection(const wchar_t *sec) {
    auto it = attrTable.find(sec);
    if (it != attrTable.end())
      return false;
    auto mSec = new IniSection();
    attrTable.insert(std::pair<std::wstring, decltype(mSec)>(sec, mSec));
    isChanged = true;
    return true;
  }

  bool IsChanged() { return this->isChanged; }
  ////Debug Method; sava file not used it
  std::wstring Print() {
    std::wstringstream wstream;
    auto an = attrTable.find(ANONYMOUSSEC);
    if (an != attrTable.end()) {
      for (auto &t : an->second->items) {
        wstream << t.key << L"=" << t.value << (isCRLF ? L"\r\n" : L"\n");
        if (!t.comments.empty())
          wstream << L"#" << t.comments << (isCRLF ? L"\r\n" : L"\n");
      }
    }
    for (const auto &it : attrTable) {
      if (it.first != ANONYMOUSSEC) {
        wstream << L"[" << it.first << L"]" << (isCRLF ? L"\r\n" : L"\n");
        for (auto &t : it.second->items) {
          wstream << t.key << L"=" << t.value << (isCRLF ? L"\r\n" : L"\n");
          if (!t.comments.empty()) {
            wstream << L"#" << t.comments << (isCRLF ? L"\r\n" : L"\n");
          }
        }
      }
    }
    return wstream.str();
  }
};

class InitializeAttribute {
private:
  std::wstring mfile;
  InitializeStructure initializeStructure;

public:
  InitializeAttribute &operator=(const InitializeAttribute &rhs) {
    /// value=value
    return *this;
  }
  InitializeAttribute(const InitializeAttribute &iattr) { operator=(iattr); }
  InitializeAttribute(const wchar_t *filePath) : mfile(filePath) {
    ////
  }
};

#endif
