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
#include <unordered_map>
#include <string>
#include <map>
#include <vector>

class InitializeStructure{
private:
    bool isChanged;
public:
    struct Parameters{
        std::wstring key;
        std::wstring value;
        std::wstring comments;
        int nOrder;
        Parameters(std::wstring k,
            std::wstring v,
            std::wstring c,
            int nOrder=0):key(k),value(v),comments(c),nOrder(nOrder){ } ///////
        Parameters(){}
    };
    struct IniSection{
        typedef std::vector<Parameters>::iterator iterator;
        iterator begin(){return items.begin();}
        iterator end(){return items.end();}
        std::wstring comment;
        std::vector<Parameters> items;
    };
    std::unordered_map<std::wstring,IniSection*> attrTable;
    ~InitializeStructure()
    {
        for(auto &i:attrTable)
        {
            if(i.second)
                delete i.second;
        }
        attrTable.clear();
    }
    std::wstring get(const wchar_t *sec,const wchar_t *key,const wchar_t *preset,int Order=0)
    {
        return preset;
    }
    bool IsChanged(){return this->isChanged;}
};

class InitializeAttribute{
private:
    std::wstring mfile;
    InitializeStructure initializeStructure;
public:
    InitializeAttribute &operator=(const InitializeAttribute &rhs){
        ///value=value
        return *this;
    }
    InitializeAttribute(const InitializeAttribute &iattr){operator=(iattr);}
    InitializeAttribute(const wchar_t *filePath):mfile(filePath)
    {
        ////
    }
};


#endif
