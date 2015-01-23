/*********************************************************************************************************
*   Phoneix Ini  Features
*   Note: IniResolve.hpp
*   Data: 2015.01.22
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_INIRESOLVE_HPP
#define PHOENIX_INIRESOLVE_HPP
#include <string>
#include <vector>
#include <map>


template<class T>//T  wstring or string
class IniResolve{
public:
    struct ParamKV{
        T key;
        T value;
        ParamKV(T k, T v) :key(k), value(v)
        {
            ////
        }
    };
protected:
    T m_iniFile;
    std::map<T, std::vector<ParamKV>> treeMode;///Node as a map->
public:
    IniResolve(T &inifile);
};

class  IniResolveUnicode :public IniResolve<std::wstring>{
public:
    IniResolveUnicode();
};

#endif
