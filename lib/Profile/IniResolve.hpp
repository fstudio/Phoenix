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
typedef enum{
    INIRESOLVE_ENCODING_ANSI=1,
    INIRESOLVE_ENCODING_UTF8_WITHOUTBOM,
    INIRESOLVE_ENCODING_UTF8_WITHBOM,
    INIRESOLVE_ENCODING_UTF16LE,
    INIRESOLVE_ENCODING_UTF16BE
}IniResolveFileEncoding;


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
    enum INI_LINE_TYPEINFO{
        INI_LINE_TYPEINFO_COMMENTS=0,
        INI_LINE_TYPEINFO_SECTIONS=1,
        INI_LINE_TYPEINFO_PARAMETERS=3
    };
protected:
    T m_iniFile;
    std::map<T, std::vector<ParametersNV> > treeMode;///Node as a map->
    std::map<unsigned,T> commentsMap;
    unsigned CheckIniFileEncoding(const char *buffer,size_t bufferSize)
    {
        ///BOM Marker Checher.
        if(bufferSize>=3)
        {
            if(buffer[0]==0xEF&&buffer[1]==0xBB&&buffer[2]==0xBF)
                return INIRESOLVE_ENCODING_UTF8_WITHBOM;
            if(buffer[0]==0xEF&&buffer[1]==0xFE)
                return INIRESOLVE_ENCODING_UTF16LE;
            if(buffer[0]==0xFF&&buffer[1]==0xFE)
                return INIRESOLVE_ENCODING_UTF16BE;
        }
        ///UniversalChardet Checker UTF8 without BOM or ANSII CodePage
        return 0;
    }
public:
    ////This Get String Type:
    typedef typename T::value_type Character;
    typedef typename T::pointer CharacterPtr;
    typedef typename T::const_pointer StringConstPtr;
    typedef typename T::reference StringRef;
    typedef typename T::const_reference StringConstRef;

    ////
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
    bool IniTextResolveAnalyzer(/*_Not_NULL_*/StringConstPtr str,size_t size)
    {
        if(str==nullptr||size<=0)
            return false;
        size_t line=0;
        return true;
    }
};


class  IniResolveUnicode :public IniResolve<std::wstring>{
public:
    IniResolveUnicode(std::wstring inifile):IniResolve<std::wstring>(inifile)
    {
        ////
    }
    bool Loader();
};

class IniResolveMultiByte :public IniResolve<std::string>{
public:
    IniResolveMultiByte(std::string inifile):IniResolve<std::string>(inifile){
        ///
    }
    bool Loader();
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

class SmapleCfgResolveUnicode:public SmapleCfgResolve<std::wstring>{
public:
    bool Loader();
};


#endif
