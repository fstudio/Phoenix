/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: GC.c This File is GC Feature
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <stddef.h>
#include <Runtime/GC.h>



PKGEXTERN void PRGC_Init()
{
    ///Init.
}

PKGEXTERN void *PRGC_Alloc(size_t mmSize)
{
  return NULL;
}

PKGEXTERN void *PRGC_Malloc(size_t mmSize)
{
  if(mmSize==0)
    return NULL;
  return NULL;
}
