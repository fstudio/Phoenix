/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: GC.c This File is GC Feature
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <stddef.h>
#include <Runtime/GC.h>


PKGEXTERN void GCInitialize()
{
    ///Init.
}

PKGEXTERN void *GCAlloc(size_t mmSize)
{
  return NULL;
}

PKGEXTERN void GCDestory()
{
    ///
}

PKGEXTERN void *GCMalloc(size_t mmSize)
{
  if(mmSize==0)
    return NULL;
  return NULL;
}
