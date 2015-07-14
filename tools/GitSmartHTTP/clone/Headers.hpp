/*

*/
#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP
#include <string>
#include <unordered_map>
#include <string.h>


class HTTPHeaders{
private:
    typedef std::unordered_map<std::wstring,std::wstring> StoreMap;
    std::unordered_map<std::wstring,std::wstring> umap;
    static bool inline HeaderKVSplit(const wchar_t *buffer,StoreMap &um)
    {
        return true;
    }
public:
    HTTPHeaders(std::wstring &header)
    {
        if(header.empty())
            return ;
        auto msize=header.size();
        auto begin=header.c_str();
        const wchar_t *index=begin;
        const wchar_t *pre=index;
        const wchar_t *end=begin+msize;
        bool cr=false;
        wchar_t buffer[4096]={0};
        while(index++<end)
        {
            if(*index=='\r')
                cr=true;
            else
                cr=false;
            if(cr&&*index=='\n')
            {
                wcsncpy(buffer,pre,index-pre-2);
            }
        }
    }
    int GetResponseCode(){
        return this->responseCode;
    }
    std::wstring header_in(const wchar_t *key){
        return umap[key];
    }
};

#endif
