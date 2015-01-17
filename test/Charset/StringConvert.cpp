#include <Windows.h>
#include <string>
#include <stdio.h>
#pragma comment(lib,"kernel32")
#pragma comment(lib,"gdi32")
#pragma comment(lib,"user32")

bool StringToWideString(const std::string &str,std::wstring &wstr)
 {
     int nLen = (int)str.length();
     wstr.resize(nLen,L' ');
     int nResult = MultiByteToWideChar(CP_ACP,0,(LPCSTR)str.c_str(),nLen,(LPWSTR)wstr.c_str(),nLen);
     if (nResult == 0)
     {
         return false;
     }
     return true;
 }
bool WideStringToString(const std::wstring &wstr,std::string &str)
 {
     int nLen = (int)wstr.length();
     str.resize(nLen,' ');
     int nResult = WideCharToMultiByte(CP_ACP,0,static_cast<LPCWSTR>(wstr.c_str()),nLen,(LPSTR)str.c_str(),nLen,NULL,NULL);
     if (nResult == 0)
     {
         return false;
     }
     return true;
 }
 
int wmain(int argc,wchar_t* argv[])
{
//MessageBoxW(nullptr,__wargv[0],L"Unicode Origin",MB_OK);
 std::string a="ANSII Test Char String";
 MessageBoxA(nullptr,a.c_str(),"ANSII Origin",MB_OK);
 std::wstring b=L"Unicode Test Char String";
 MessageBoxW(nullptr,b.c_str(),L"Unicode Origin",MB_OK);
 std::wstring c;
 std::string d;
 StringToWideString(a,c);
 WideStringToString(b,d);
 MessageBoxW(nullptr,c.c_str(),L"Change to Unicode",MB_OK);
  MessageBoxA(nullptr,d.c_str(),"Change to ANSII",MB_OK);
 return 0;
}
 