/*********************************************************************************************************
* Arguments.hpp
* Note: Phoenix Arguments
* Data: 2015.05.02
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_ARGUMENTS_HPP
#define PHOENIX_ARGUMENTS_HPP
#ifdef _WIN32
#include <Windows.h>
#define strdup _strdup
#endif
#include <string>
#include <string.h>
#include <codecvt>


inline std::string ToNarrow(const std::wstring &wstr)
{
    std::string str;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    str=conv.to_bytes(wstr);
    return str;
}

inline std::string ToNarrow(const wchar_t  *wstr)
{
    std::wstring w=wstr;
    return ToNarrow(w);
}

inline char* ToNarrowDup(const wchar_t *wstr)
{
    std::wstring w=wstr;
    std::string str;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    str=conv.to_bytes(wstr);
    char *p=strdup(str.c_str());
    return p;
}

class Arguments{
public:
    static Arguments Main(int argc,char const * const *argv)
    {
#ifdef _WIN32
        (void)argc;
        (void)argv;
        int ac;
        LPWSTR *w_av=CommandLineToArgvW(GetCommmandLineW(),&ac);
        std::vector<std::string> av1(ac);
        std::vector<char const *> av2(ac);
        for(int i=0;i<ac;i++)
        {
            av[i]=ToNarrow(w_av[i]);
            av2[i]=av1[i].c_str();
        }
        LocalFree(w_av);
        return Arguments(ac,&ac2[0]);
#else
        return Arguments(argc,argv);
#endif
    }
    Arguments(int argc,char const *const *argv)
    {
        this->argv_.resize(argc+1);
        for(int i=0;i<argc;i++)
        {
            this->argv_[i]=strdup(argv[i]);
        }
        this->argv_[argc]=0;
    }
    Arguments(int argc,wchar_t const *const *argv)
    {
        ///
        this->argv_.resize(argc+1);
        for(int i=0;i<argc;i++)
        {
            this->argv_[i]=ToNarrowDup(argv[i]);
        }
        this->argv_[argc]=0;
    }
    ~Arguments()
    {
        for(auto &i:this->argv_)
        {
            free(i);
        }
    }
    Arguments(const Arguments &other)
    {
        this->argv_.resize(other.argv_.size());
        for (size_t i = 0; i < this->argv_.size(); i++) {
            this->argv_[i] = other.argv_[i] ? strdup(other.argv_[i]) : 0;
        }
    }
    Arguments &operator=(const Arguments &)
    {
        if (this != &other) {
            size_t i;
            for (i = 0; i < this->argv_.size(); i++) {
                free(this->argv_[i]);
            }
            this->argv_.resize(other.argv_.size());
            for (i = 0; i < this->argv_.size(); i++) {
                this->argv_[i] = other.argv_[i] ? strdup(other.argv_[i]) : 0;
            }
        }
        return *this;
    }
    int argc() const
    {
        return static_cast<int>(this->argv_.size()-1);
    }
    char const *const *argv() const
    {
        return &this->argv_[0];
    }
protected:
    std::vector<char *> argv_;
};


#endif

