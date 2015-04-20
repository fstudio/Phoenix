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

template <class Character>
class FlavorlessWriter{
public:
    typedef basic_stringstream<Character> Stringstream;
    /*FlavorlessWriter(const FlavorlessWriter &fw)
    {
        ///
    }*/
    bool Save()
    {
        return true;
    }
private:
    Stringstream stream;
};


#endif
