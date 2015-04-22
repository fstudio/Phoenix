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
#error "Only Support Windows System"
#endif
#include <unordered_map>
#include <string>
#include <vector>


class InitializeStructure{
public:
    struct Section{
        std::wstring keyName;
        std::unordered_map<std::wstring,std::wstring> attrTable;
        std::unordered_map<unsigned,std::wstring> comments;
    };
    std::vector<Section*> attrVector
    ~InitializeStructure()
    {
        for(auto &i:attrVector)
        {
            if(i)
                delete i;
        }
        attrVector.clear();
    }
};

class InitializeAttribute{
private:
    std::wstring mfile;
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
