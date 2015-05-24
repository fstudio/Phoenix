/*********************************************************************************************************
* FontAwesome.cpp
* Note: Phoenix FontAwesome
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <string>
#include <Windows.h>
#include <Wingdi.h>
#include "FontAwesome.hpp"
#include "Direct2D.hpp"


#define AWESOMEFONTNAME L"FontAwesome"



HRESULT CreateFontFaceFromFontFile(const wchar_t* FontFileName, IDWriteFontFace **ppFontFace)
{
    HRESULT hr = S_OK;

    IDWriteFactory* pDWriteFactory = NULL;
    IDWriteFontFace* pFontFace = NULL;
    IDWriteFontFile* pFontFiles = NULL;

    // Create the DirectWrite factory.
    hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(&pDWriteFactory)
            );

    if (SUCCEEDED(hr))
    {
        hr = pDWriteFactory->CreateFontFileReference(
            FontFileName,
            NULL,
            &pFontFiles);
    }

    IDWriteFontFile* fontFileArray[] = {pFontFiles};
    if (SUCCEEDED(hr))
    {
        hr = pDWriteFactory->CreateFontFace(
            DWRITE_FONT_FACE_TYPE_TRUETYPE,
            1, // file count
            fontFileArray,
            0,
            DWRITE_FONT_SIMULATIONS_NONE,
            &pFontFace
            );
    }

    //Return the pointer to the caller
    *ppFontFace = pFontFace;

    SafeRelease(&pDWriteFactory);
    SafeRelease(&pFontFiles);

    return hr;
}


FontAwesome::FontAwesome(std::wstring& fontfile):loadOK(false)
{
    if(AddFontResourceExW(fontfile.c_str(),FR_PRIVATE,0)==0)
     return;
     loadOK=true;
     m_fontfile=fontfile;
    ::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
}

FontAwesome::~FontAwesome()
{
  if(loadOK){
    RemoveFontResourceEx(m_fontfile.c_str(),FR_PRIVATE,0);
    ::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
  }
}

HFONT FontAwesome::CreateAwesomeFont(long height)
{
  HFONT hFont = (HFONT) GetStockObject(DEFAULT_GUI_FONT);
  LOGFONT logFont = { 0 };
  GetObject(hFont, sizeof(logFont), &logFont);
  DeleteObject(hFont);
  hFont = NULL;
  logFont.lfHeight = height;
  logFont.lfWeight = FW_NORMAL;
  logFont.lfCharSet = DEFAULT_CHARSET;
  wcscpy_s(logFont.lfFaceName, AWESOMEFONTNAME);
 return CreateFontIndirect(&logFont);
}

const wchar_t *FontAwesome::GetFontAwesomeName()
{
    return AWESOMEFONTNAME;
}
