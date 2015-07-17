/*
*/
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP
#include <string>
#include <unordered_map>


typedef std::unordered_map<std::wstring,std::wstring> HeaderKv;

class Request{
private:
    std::wstring m_url;
    HeaderKv header;
public:
    Request(const wchar_t* url=nullptr);
    Request(std::wstring &url);
    bool HeaderOut(const wchar_t *key,std::wstring &value);
};

#endif
