/*********************************************************************************************************
* Header.hpp
* Note: Phoenix Main Header.hpp
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_HEADER_HPP
#define PHOENIX_HEADER_HPP
#ifndef _WINDOWS_
#include <windows.h>
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

#endif
