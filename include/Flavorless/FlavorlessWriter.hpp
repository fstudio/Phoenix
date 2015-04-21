/*********************************************************************************************************
* FlavorlessWriter.hpp
* Note: Phoenix Flavorless Library
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef FLAVORLESS_WRITER_HPP
#define FLAVORLESS_WRITER_HPP
#include <sstream>


inline bool WriteLine(std::string line)
{
    return true;
}


template <class Character>
class FlavorlessWriter{
public:
    typedef std::basic_stringstream<Character> Stringstream;
    /*FlavorlessWriter(const FlavorlessWriter &fw)
    {
        ///
    }*/
    bool Save(InitializeStructure &iniStructure)
    {
        return true;
    }
private:
    Stringstream stream;
};


#endif
