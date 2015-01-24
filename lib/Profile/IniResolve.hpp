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

/**
#this comments .
;Ini File Format Like this:
[Sections]
a=b
a=c
a=d
b=e
[Sections]
name=value
;sections
**/

template<class T>//T  wstring or string
class IniResolve{
public:
    struct ParametersNV{
        T name;
        T value;
        ParametersNV(T n, T v) :name(n), value(v)
        {
            ////
        }
    };
protected:
    T m_iniFile;
    std::map<T, std::vector<ParametersNV> > treeMode;///Node as a map->
    unsigned CheckIniFileEncoding(const char *buffer,size_t bufferSize)
    {
        return 0;
    }
public:
    typedef typename T::const_pointer StringConstPtr;
    IniResolve(T &inifile):m_iniFile(inifile)
    {
        //
    }
    T Get(StringConstPtr section,StringConstPtr name,unsigned innode=0)
    {
        return Get(T(section),T(name),innode);
    }
    T Get(T section,T sname,unsigned innode=0)
    {
        auto &v=treeMode[section];
        auto iter=v.begin();
        auto end=v.end();
        for(;iter!=end;iter++)
        {
            if(iter->name==sname)
                return iter->value;
        }
        return T(5,0);
    }
    bool Set(T section,T name,T value,unsigned innode=0)
    {
        auto &v=treeMode[section];
        return false;
    }
    bool Set(StringConstPtr section,StringConstPtr name,StringConstPtr value,unsigned innode=0)
    {
        return Set(T(section),T(name),T(value),innode);
    }
};


class  IniResolveUnicode :public IniResolve<std::wstring>{
public:
    IniResolveUnicode(std::wstring inifile):IniResolve<std::wstring>(inifile)
    {
        ////
    }
};

class IniResolveMultiByte :public IniResolve<std::string>{
public:
    IniResolveMultiByte(std::string inifile):IniResolve<std::string>(inifile){
        ///
    }
};

/**
;Smaple Cfg File Like this:
[section]
value1
value2
value3
value4
[section2]
value1
value2
**/

template<class T>
class SmapleCfgResolve{
protected:
    std::map<T,std::list<T>> CfgListTable;
    T cfgFile;
public:
    void Init(T& cfgFile)
    {
        this->cfgFile=cfgFile;
    }
};




#endif
