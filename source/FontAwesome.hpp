/*********************************************************************************************************
* FontAwesome.hpp
* Note: Phoenix FontAwesome
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_FONTAWESOME_HPP
#define PHOENIX_FONTAWESOME_HPP

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#define NAME_AWESOME_ICON_ENABLE 1
#define AWESOME_ICON_GLASS 0xF000
#define AWESOME_ICON_MUSIC 0xF001


class FontAwesome{
private:
 std::wstring m_fontfile;
 bool loadOK;
public:
  FontAwesome(std::wstring& fontfile);
  ~FontAwesome();
  static HFONT CreateAwesomeFont(long height);
  static const wchar_t *GetFontAwesomeName();
std::wstring getFontFileName(){ return this->m_fontfile; }
};



#endif
