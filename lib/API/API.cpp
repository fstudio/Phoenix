/*********************************************************************************************************
*   Phoneix Plugin API Interface
*   Note: API.cpp
*   Data: 2015.01.17
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Phoneix.h>

static version_t sgversion={
   PHOENIX_VERSION_MAJRO,0,0,0
};

extern "C" unsigned GetMajroVersion(void)
{
  return PHOENIX_VERSION_MAJRO;
}

extern "C" version_t GetVersionTypoe(void)
{
    return sgversion;
}
