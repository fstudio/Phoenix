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
#include <list>
#include <map>


template<class T>//T  wstring or string
class IniResolve{
private:
    T m_iniFile;
    std::map<T,std::map<T,T>> iniNodeKV;///Node as a map->
public:
    IniResolve(T &inifile);
};

class POENIX_NO_VTABLE IniResolveUnicode:public IniResolve<std::wstring>{
public:
    IniResolveUnicode();
};

#endif
