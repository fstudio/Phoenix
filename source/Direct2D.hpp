/*********************************************************************************************************
* Direct2D.hpp
* Note: Phoenix Editor Direct2D Header
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef PHOENXI_DIRECT2D_HPP
#define PHOENXI_DIRECT2D_HPP

#include <d2d1.h>
#include <dwrite.h>
#include <Strsafe.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib,"dwrite.lib")

#ifndef ASSERT
#ifdef _DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#define ASSERT_HERE assert(FALSE)
#else // _DEBUG
#define ASSERT(x)
#define ASSERT_HERE
#endif //_DEBUG
#endif // ASSERT


template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
  if (*ppInterfaceToRelease != nullptr) {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = nullptr;
  }
}

#define DO(action)                                                             \
  if (FAILED( action )) {                                                        \
    ASSERT( FALSE );                                                             \
    goto ClenUp;                                                               \
  }


template <class T>
class Direct2DEx{
public:
    Direct2DEx():Ptr(nullptr)
    {
        //
    }
    ~Direct2DEx()
    {
        if(Ptr)
            Ptr->Release();
    }
    T *Ptr;
};


HRESULT LoadResourceBitmap(
    ID2D1RenderTarget* pRendertarget,
    IWICImagingFactory* pIWICFactory,
    PCWSTR resourceName,
    PCWSTR resourceType,
    UINT destinationWidth,
    UINT destinationHeight,
    ID2D1Bitmap** ppBitmap
    );

#endif
