/*********************************************************************************************************
* Flavorless.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_LIBRARY_HPP
#define FLAVORLESS_LIBRARY_HPP
#include "FlavorlessInternal.h"
#include "FlavorlessLoader.hpp"
#include "FlavorlessWriter.hpp"


#define FLAVORLESS_VERSION_CODE(x,y,z) \
  (((x)*100000) + ((y)*100) + (z))

//FlavorlessInitial
//not support UTF32 encoding
template<class Character>
class FlavorlessImpl{
public:
    typedef std::base_string<Character> String;
private:
    bool isUpdate;
    FlavorTP  rawType;
    FlavorlessLoader loader;
    FlavorlessWriter writer;
    InitializeStructure iniStructure;
public:
    FlavorlessImpl():isUpdate(false),rawType(FlavorTP::FILETYPE_UNKNWON)
    {
        //////
    }
    bool Initialize(const Character *file)
    {
        rawType=loader.Detect(file);
        if(rawType==FlavorTP::FILETYPE_FAILED)
            return false;
        return loader.Loader(file,this->iniStructure);
    }
    String get(const Character *key,const Character *node,const Character *preset=nullptr)
    {
        if(!key)
            return String();
        return preset;
    }
    bool set(const Character *key,const Character *node,const Character value)
    {
        isUpdate=true;
        return true;
    }
    bool RemoveSection(const Character *node)
    {
        isUpdate=true;
        return true;
    }
    bool Save()
    {
        bool bRet=true;
        if(isUpdate||loader.IsChanged())
        {
            ////
            writer.Save(this->iniStructure);
        }else{
            return true;
        }
        return bRet;
    }
    void Clear()
    {
        ///
    }
};
typedef FlavorlessImpl<wchar_t> FlavorlessWide;
typedef FlavorlessImpl<char> FlavorlessA;

#ifdef _WIN32
#define Flavorless FlavorlessWide
#else
#define Flavorless FlavorlessA
#endif

#endif
