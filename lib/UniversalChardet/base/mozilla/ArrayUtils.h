/*********************************************************************************************************
* ArrayUtils.h mozilla/ArrayUtils.h replace.
* Thanks Mozilla Foundation
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoenix Universial Chardet Library
* E-mail:<forcemz@outlook.com>
* @2015.01
**********************************************************************************************************/
#ifndef UNIVERSAL_CHARDET_MOZILLA_ARRAYUTILS_H
#define UNIVERSAL_CHARDET_MOZILLA_ARRAYUTILS_H

namespace mozilla{
	inline size_t ArrayLength(const int16_t x[])
	{
		return (sizeof(x) / sizeof(x[0]));
	}
}

#endif
