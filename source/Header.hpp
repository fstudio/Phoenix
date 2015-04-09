/*********************************************************************************************************
* Header.hpp
* Note: Phoenix Main Header.hpp
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_HEADER_HPP
#define PHOENIX_HEADER_HPP
#ifndef _WINDOWS_
#include <windows.h>
#endif
#include <string>
#include <vector>

#ifndef MAX_UNC_PATH
#define MAX_UNC_PATH (32*1024-1)
#endif


class ForceHANDLE{
public:
    HANDLE m_handle;
    ForceHANDLE()
    {
        m_handle=nullptr;
    }
    ForceHANDLE(HANDLE hPtr)
    {
        if(hPtr)
            this->m_handle=hPtr;
    }
    HANDLE Get() const{
        return this->m_handle;
    }
    ~ForceHANDLE()
    {
        if(m_handle)
        {
            CloseHandle(m_handle);
            m_handle=nullptr;
        }
    }
    bool Delete()
    {
        if(m_handle)
        {
            CloseHandle(m_handle);
            m_handle=nullptr;
        }
    }
    ForceHANDLE& operator=(HANDLE hPtr)
    {
        m_handle=static_cast<HANDLE>(hPtr);
        return *this;
    }
    ForceHANDLE& operator=(const ForceHANDLE &forceHandle)
    {
        this->m_handle=static_cast<HANDLE>(forceHandle.Get());
        return *this;
    }
};

struct Parameters{
    std::vector<std::wstring> filevector;
    bool model;
};

template <class T,class TVaule>
class AutoRelease{
private:
    T callback;
    TVaule value;
public:
    AutoRelease(T cb,TVaule va):callback(cb),value(va)
    {
        //
    }
    ~AutoRelease()
    {
        callback(value);
    }
};

#define AUTO_RELEASEZ(x,y) AutoRelease<decltype(x),decltype(y)>(x,y) ar
#endif
