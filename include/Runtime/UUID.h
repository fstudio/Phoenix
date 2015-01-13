/****************************************************************************************************************
* Phoenix Package Runtime Library UUID
* Author:Force
* E-mail: forcemz@outlook.com
* Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_UUID_H
#define PHOENIX_PACKAGE_RUNTIME_UUID_H
#include "rtdefs.h"
#include <stdint.h>

typedef struct CharlieUUID{
   uint32_t Data1;
   uint16_t Data2;
   uint16_t Data3
   uint8_t Data4[8];
}CharlieUUID;



#endif
