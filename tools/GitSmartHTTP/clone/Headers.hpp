/*

*/
#ifndef HTTP_HEADERS_HPP
#define HTTP_HEADERS_HPP
#include <string>
#include <unordered_map>
class HTTPHeaders{
private:
    int responseCode;
    std::unordered_map<std::wstring,std::wstring> umap;
public:
    HTTPHeaders(std::wstring &header)
    {
        //////
    }
    int GetResponseCode(){
        return this->responseCode;
    }
    std::wstring header_in(const wchar_t *key){
        return umap[key];
    }
};

#endif
