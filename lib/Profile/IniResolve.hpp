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
#include <regex>
#include <list>
#include <UniversalChardet/UniversalChardet.h>
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
//Legolas

template<class T>//T  wstring or string
class IniResolve{
public:
    typedef typename T::value_type Character;
    typedef typename T::pointer CharacterPtr;
    typedef typename T::const_pointer StringConstPtr;
    typedef typename T::reference StringRef;
    typedef typename T::const_reference StringConstRef;
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
    bool Modify;
    std::map<T, std::vector<ParametersNV> > treeMode;///Node as a map->
    std::map<unsigned,T> commentsMap;
    std::vector<ParametersNV> anonymousNV;
    T currentSection;
    std::vector<ParametersNV>* currentPtr;//current vector cache Pointer.
    unsigned codePage;
    bool isBom;
    bool CheckIniFileChardet()
    {
        int ret=0;
        if((ret=UniversalChardetFromFilePath(this->m_iniFile,this->isBom))<=0)
            return false;
        this->codePage=ret;
        return true;
    }
public:
    IniResolve(T &inifile):m_iniFile(inifile),
    Modify(false),
    isBom(false)
    {
        //
        currentPtr=&(this->anonymousNV);//Move Pointer to anonymous Parameters Name Value.
    }
    ~IniResolve()
    {
    }
    T Get(StringConstPtr section,StringConstPtr name,unsigned innode=0)
    {
        return Get(T(section),T(name),innode);
    }
    T Get(T section,T sname,unsigned innode=0)
    {
        if(section.empty)
        {
            auto it=anonymousNV.begin();
            auto end=anonymousNV.end();
            for(;it!=end;it++)
            {
                it->name==sname;
                return it->value;
            }
            return std::string();
        }
        auto it2=treeMode.find(section);
        if(it2==treeMode.end())
        {
            return T();
        }
        auto &v=treeMode[section];
        auto iter=v.begin();
        auto end=v.end();
        std::vector<T> va;
        for(;iter!=end;iter++)
        {
            if(iter->name==sname)
                va.push_back(iter->value);
        }
        if(va.size()>=1)
        {
            if(innode>va.size())
                return va[va.size()-1];
            return va[innode];
        }
        return T();
    }
    bool Set(T section,T name,T value,unsigned innode=0)
    {
        if(name.empty())
            return false;
        if(section.empty())
        {
            auto it=anonymousNV.begin();
            auto end=anonymousNV.end();
            for(;it!=end;it++)
            {
                if(it->name==name)
                {
                    it->value=value;
                    return true;
                }
            }
            ParametersNV nv(name,value);
            anonymousNV.push_back(nv);
            return true;
        }
        auto it=treeMode.find(section);
        if(it==treeMode.end()){
            std::vector<ParametersNV> v;
            treeMode.insert(std::map<T, decltype(v)>::value_type(section,v));
        }
        auto &v=treeMode[section];
        auto iter=v.begin();
        auto end=v.end();
        unsigned i=0;
        for(;iter!=end;iter++)
        {
            if(iter->name==name)
            {
                if(value.empty()){
                    v.erase(iter);
                    return true;
                }
                if(i<innode){
                    i++;
                }else{
                    iter->value=value;
                }
                ////DONE
            }
        }
        return true;
    }
    bool Set(StringConstPtr section,StringConstPtr name,StringConstPtr value,unsigned innode=0)
    {
        if(section==nullptr)
        {
            return Set(T(),T(name),T(value),innode);/// T()null
        }
        return Set(T(section),T(name),T(value),innode);
    }
    bool IniTextResolveAnalyzerLine(const T &str)
    {
        size_t pos;
        /// ; 0x3B # 0x23
        if(str.at(0)==static_cast<Character>(';')||str.at(0)==static_cast<Character>('#')||(str.at(0)=='/'&&str.size()>2&&str.at(1)=='/'))
        {
            commentsMap.insert(std::pair<unsigned,T>(this->treeMode.size(),str));
        }else if(str[0]==static_cast<Character>('[')&&(pos=str.find(static_cast<Character>(']')))!=T::npos) //[ 0x5B ] 0x5D
        {
            std::vector<ParametersNV> v;
            T sn=str.substr(1,pos-1);
            treeMode.insert(std::pair<T,std::vector<ParametersNV>>(sn,v));
            currentSection=sn;
            currentPtr=&treeMode[sn];
            ///.
        }else if((pos=str.find_first_of(static_cast<Character>('=')))!=T::npos) // = 0x3D : 0x3A
        {
            ParametersNV pNv(str.substr(0,pos-1),str.substr(pos+1,str.size()-pos-1));///key=value,
            currentPtr->push_back(pNv);
        }
        return true;
    }
    bool IniTextResolveAnalyzerLine(/*_Not_NULL_*/StringConstPtr str,size_t size)
    {
        if(str==nullptr||size<=0)
            return false;
        auto i=0;
        StringConstPtr Ptr;
        if(str[0]=='#'||str[0]==';')
        {
            if(size>=2){
                T commentsStr=str;
                commentsMap.insert(std::pair<unsigned,T>(this->treeMode.size(),commentsStr));
                return true;
            }
            return true;
        }else if(str[0]=='['&&str[1]!=']'){
            Ptr=&str[1];
            while(i<size-1)
            {
                if(Ptr[i++]==']')
                {
                    std::vector<ParametersNV> v;
                    T sn=T(Ptr,i-1);
                    treeMode.insert(std::pair<T,std::vector<ParametersNV>>(sn,v));
                    currentSection=sn;
                    currentPtr=&treeMode[sn];
                    return true;
                }
            }
            return false;
            //
        }else{
            //
            while(i<size)
            {
                if(str[i++]=='=')
                {
                    T key=T(str,i-1);
                    if(i<size-2)
                    {
                        Ptr=&str[i];
                        ParametersNV pNv(key,T(Ptr));///key=value,
                        currentPtr->push_back(pNv);
                        return true;
                    }
                    return false;
                }
            }
        }
        return false;
    }
    bool IniTextResolveAnalyzer(CharacterPtr cPtr,size_t size)
    {
        ///
        Character lineBase[8192]={0};
        size_t index(0),Pre(0),index2(0);
        while(index<size)
        {
            if((lineBase[index2++]=cPtr[index++])=='\n')
            {
                lineBase[index2--]='\0';
                T s=T(lineBase);
                size_t n=0;
                if((n=s.find('\r'))!=T::npos)
                {
                    s.erase(n,1);
                }
                this->IniTextResolveAnalyzerLine(s);
                index2=0;
            }
        }
        return true;
    }
};


class  IniResolveUnicode :public IniResolve<std::wstring>{
private:
    bool GetTransactedLine(std::string raw,std::wstring &det);
    bool ForeachReaderLineA();
    bool ForeachReaderLineW();
    bool ForeachReaderLineBE();
public:
    IniResolveUnicode(std::wstring inifile):IniResolve<std::wstring>(inifile)
    {
        ////
    }
    bool Loader();
    bool Save();//Sava With Origin Encoding
    bool SaveWithUTF16LE();//Sava With Uncode.
};

class IniResolveMultiByte :public IniResolve<std::string>{
private:
    bool GetTransactedLine(std::wstring raw,std::string &det);
    bool ForeachReaderLineA();
    bool ForeachReaderLineW();
public:
    ////Init Regex.
    IniResolveMultiByte(std::string inifile):IniResolve<std::string>(inifile){
        ///
    }
    bool Loader();
    bool Save();
    bool SaveWithUTF8();//Sava With UTF-8 default has BOM.
    bool SaveWithUTF8NoBOM();
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
