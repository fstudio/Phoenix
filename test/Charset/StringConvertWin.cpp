
#include <string>
#include <Windows.h>




std::wstring MultiCharToUnicode(const std::string &str) {
  int len = 0;
  len = str.length();
  int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pUnicode;
  pUnicode = new wchar_t[unicodeLen + 1];
  memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
  ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, (LPWSTR)pUnicode,
                        unicodeLen);
  std::wstring rt;
  rt = (wchar_t *)pUnicode;
  delete pUnicode;

  return rt;
}
std::string UnicodeToMultiChar(const std::wstring &str) {
  char *pElementText;
  int iTextLen;
  // wide char to multi char
  iTextLen =
      WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
  pElementText = new char[iTextLen + 1];
  memset((void *)pElementText, 0, sizeof(char) * (iTextLen + 1));
  ::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pElementText, iTextLen,
                        NULL, NULL);
  std::string strText;
  strText = pElementText;
  delete[] pElementText;
  return strText;
}
std::wstring UTF8ToUTF16(const std::string &str) {
  int len = 0;
  len = str.length();
  int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
  wchar_t *pUnicode;
  pUnicode = new wchar_t[unicodeLen + 1];
  memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
  ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, (LPWSTR)pUnicode,
                        unicodeLen);
  std::wstring rt;
  rt = (wchar_t *)pUnicode;
  delete pUnicode;

  return rt;
}
std::string UTF16ToUTF8(const std::wstring &str) {
  char *pElementText;
  int iTextLen;
  // wide char to multi char
  iTextLen =
      WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
  pElementText = new char[iTextLen + 1];
  memset((void *)pElementText, 0, sizeof(char) * (iTextLen + 1));
  ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, pElementText, iTextLen,
                        NULL, NULL);
  std::string strText;
  strText = pElementText;
  delete[] pElementText;
  return strText;
}
