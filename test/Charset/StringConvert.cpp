#include <Windows.h>
#include <string>
#include <stdio.h>
#pragma comment(lib,"kernel32")
#pragma comment(lib,"gdi32")
#pragma comment(lib,"user32")

bool StringToWideString(const std::string &str,std::wstring &wstr)
 {
 int  len = 0;
 len = str.length();
 int  unicodeLen = ::MultiByteToWideChar( CP_ACP,
            0,
            str.c_str(),
            -1,
            NULL,
            0 );  
 wchar_t *  pUnicode;  
 pUnicode = new  wchar_t[unicodeLen+1];  
 memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
 ::MultiByteToWideChar( CP_ACP,
         0,
         str.c_str(),
         -1,
         (LPWSTR)pUnicode,
         unicodeLen );  
		 wstr=pUnicode;
 delete  pUnicode; 
     return true;
 }
bool WideStringToString(const std::wstring &wstr,std::string &str)
 {
 char*     pElementText;
 int    iTextLen;
 // wide char to multi char
 iTextLen = WideCharToMultiByte( CP_ACP,
         0,
         wstr.c_str(),
         -1,
         NULL,
         0,
		 NULL,
         NULL );
 pElementText = new char[iTextLen + 1];
 memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
 ::WideCharToMultiByte( CP_ACP,
         0,
         wstr.c_str(),
         -1,
         pElementText,
         iTextLen,
         NULL,
         NULL );
  str= pElementText;
  delete[] pElementText;
  return true;
 }
 
int wmain(int argc,wchar_t* argv[])
{
//MessageBoxW(nullptr,__wargv[0],L"Unicode Origin",MB_OK);
 std::string a="ANSII Test Char String 这是一个测试字符串\0";
 MessageBoxA(nullptr,a.c_str(),"ANSII Origin",MB_OK);
 std::wstring b=L"Unicode Test Char String 这是一个测试字符串\0";
 MessageBoxW(nullptr,b.c_str(),L"Unicode Origin",MB_OK);
 std::wstring c;
 std::string d;
 StringToWideString(a,c);
 WideStringToString(b,d);
 MessageBoxW(nullptr,c.c_str(),L"Change to Unicode",MB_OK);
  MessageBoxA(nullptr,d.c_str(),"Change to ANSII",MB_OK);
 return 0;
}
 