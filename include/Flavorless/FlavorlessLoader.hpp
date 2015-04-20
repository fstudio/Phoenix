/*********************************************************************************************************
* FlavorlessLoader.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_LOADER_HPP
#define FLAVORLESS_LOADER_HPP
#include <fstream>


template<class Character>
class FlavorlessLoader{
public:
    typedef basic_fstream<Character> Fstream;
    typedef basic_string<Character> String;
    FlavorlessLoader(){}
    bool Loader(const Character *filePtr)
    {
        return true;
    }
};

#endif
