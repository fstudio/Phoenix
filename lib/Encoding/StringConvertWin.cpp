/*********************************************************************************************************
*   Phoneix Encoding Convert Win
*   Note: StringConvertWin.cpp
*   Date: 2015.01.17
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <string>
#include <Windows.h>



///Defalut CodePage

////Input CodePage
std::wstring MultiByteToUnicode(const std::string &str,unsigned cp) {
  int len = 0;
  len = str.length();
  int unicodeLen = ::MultiByteToWideChar(cp, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pUnicode;
  pUnicode = new wchar_t[unicodeLen + 1];
  memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
  ::MultiByteToWideChar(cp, 0, str.c_str(), -1, (LPWSTR)pUnicode,
                        unicodeLen);
  std::wstring rt;
  rt = (wchar_t *)pUnicode;
  delete pUnicode;

  return rt;
}
std::string UnicodeToMultiByte(const std::wstring &wstr,unsigned cp) {
  char *pElementText;
  int iTextLen;
  // wide char to multi char
  iTextLen =
      WideCharToMultiByte(cp, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
  pElementText = new char[iTextLen + 1];
  memset((void *)pElementText, 0, sizeof(char) * (iTextLen + 1));
  ::WideCharToMultiByte(cp, 0, wstr.c_str(), -1, pElementText, iTextLen,
                        NULL, NULL);
  std::string strText;
  strText = pElementText;
  delete[] pElementText;
  return strText;
}

std::wstring MultiByteToUnicode(const std::string &str) {
  return MultiByteToUnicode(str,CP_ACP);
}
std::string UnicodeToMultiByte(const std::wstring &wstr) {
  return UnicodeToMultiByte(wstr,CP_ACP);
}

////////UTF-8
std::wstring UTF8ToUnicode(const std::string &str) {
  return MultiByteToUnicode(str,CP_UTF8);
}
std::string UnicodeToUTF8(const std::wstring &wstr) {
  return UnicodeToMultiByte(wstr,CP_UTF8);
}
