/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: StringBuffer, copy from coreclr
*   Date: 2015.04.04
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <Runtime/utilcode.h>

class StringBuffer {
    static const int m_defaultSize = 4096;
    wchar_t* m_buffer;
    size_t m_capacity;
    size_t m_length;

    StringBuffer(const StringBuffer&);
    StringBuffer& operator =(const StringBuffer&);

public:
    StringBuffer() : m_capacity(0), m_buffer(nullptr), m_length(0) {
    }

    ~StringBuffer() {
        delete[] m_buffer;
    }

    const wchar_t* CStr() const {
        return m_buffer;
    }

    void Append(const wchar_t* str, size_t strLen) {
        if (!m_buffer) {
            m_buffer = new wchar_t[m_defaultSize];
            m_capacity = m_defaultSize;
        }
        if (m_length + strLen + 1 > m_capacity) {
            size_t newCapacity = m_capacity * 2;
            wchar_t* newBuffer = new wchar_t[newCapacity];
            wcsncpy_s(newBuffer, newCapacity, m_buffer, m_length);
            delete[] m_buffer;
            m_buffer = newBuffer;
            m_capacity = newCapacity;
        }
        wcsncpy_s(m_buffer + m_length, m_capacity - m_length, str, strLen);
        m_length += strLen;
    }
};

class StringBufferA {
    static const int m_defaultSize = 4096;
    char* m_buffer;
    size_t m_capacity;
    size_t m_length;

    StringBufferA(const StringBufferA&);
    StringBufferA& operator =(const StringBufferA&);

public:
    StringBufferA() : m_capacity(0), m_buffer(nullptr), m_length(0) {
    }

    ~StringBufferA() {
        delete[] m_buffer;
    }

    const char* CStr() const {
        return m_buffer;
    }

    void Append(const char* str, size_t strLen) {
        if (!m_buffer) {
            m_buffer = new char[m_defaultSize];
            m_capacity = m_defaultSize;
        }
        if (m_length + strLen + 1 > m_capacity) {
            size_t newCapacity = m_capacity * 2;
            char* newBuffer = new char[newCapacity];
            strncpy_s(newBuffer, newCapacity, m_buffer, m_length);
            delete[] m_buffer;
            m_buffer = newBuffer;
            m_capacity = newCapacity;
        }
        strncpy_s(m_buffer + m_length, m_capacity - m_length, str, strLen);
        m_length += strLen;
    }
};

extern "C" PKGEXTERN StringBufferEx StringBufferNew()
{
    StringBufferA *strbuffer=new StringBufferA();
    return strbuffer;
}

extern "C" PKGEXTERN void StringBufferDelete(StringBufferEx *buffer)
{
    if(*buffer){
        delete *buffer;
        *buffer=nullptr;
    }
}
extern "C" PKGEXTERN bool StringBufferAppend(StringBufferEx buffer,const char* str, size_t strLen)
{
    if(!buffer)
        return false;
    auto bu=reinterpret_cast<StringBufferA *>(buffer);
    bu->Append(str,strLen);
    return true;
}

extern "C" PKGEXTERN const char *StringBufferCStr(StringBufferEx buffer)
{
    if(!buffer)
        return nullptr;
    auto bu=reinterpret_cast<StringBufferA *>(buffer);
    return bu->CStr();
}
