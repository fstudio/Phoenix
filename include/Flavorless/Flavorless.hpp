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
#include <unordered_map>
#include "FlavorlessLoader.hpp"
#include "FlavorlessWriter.hpp"


#define FLAVORLESS_VERSION_CODE(x,y,z) \
  (((x)*100000) + ((y)*100) + (z))

//FlavorlessInitial 
//not support UTF32 encoding
template<class Character>
class Flavorless{
public:
    typedef std::base_string<Character> String;
private:
    FlavorTP  rawType;
    std::unordered_map<String,String> nov;
    std::list<std::unordered_map<String,String>> nodelist
public:
    String get(const Character *key,const Character *node,const Character *preset=nullptr)
    {
        if(!key)
            return String();
        if(!node)
        {
            if(nov.find(key)!=nov.end())
                return nov.at(key);
            return preset;
        }
        return preset;
    }
    bool set(const Character *key,const Character *node,const Character value)
    {

        return true;
    }
    bool RemoveSection(const Character *node)
    {
        return true;
    }
    void Clear()
    {
        nov.clear();
        nodelist.clear();
    }
};
typedef Flavorless<wchar_t> FlavorlessWide;
typedef Flavorless<char> FlavorlessA;

#endif
