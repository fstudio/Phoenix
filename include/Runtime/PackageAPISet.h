/****************************************************************************************************************
* Phoenix Package Runtime Library
* Author:Force
* E-mail: forcemz@outlook.com
* Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifdef PHOENIX_PACKAGE_RUNTIME_API
#define PHOENIX_PACKAGE_RUNTIME_API

#include "rtdefs.h"


#define PKG_RUNTIME_API_MAJOR  1
#define PKG_RUNTIME_API_MINOR  0
#define PKG_RUNTIME_API_FIXOR    0
#define PKG_RUNTIME_API_BULIDOR  0

#define PKG_RUNTIME_API_APISET_STR "Phoenix.Package.Runtime.API.v1"


typedef struct PKGRuntimeAPIVersion__{
	int major;
	int minor;
	int fixor;
	int buildor;
}PKGRuntimeAPIVersion;






#endif
