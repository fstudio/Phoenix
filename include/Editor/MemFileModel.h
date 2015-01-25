/*********************************************************************************************************
* MemFileMode.h
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
* Note: Phoenix Memory File Model header
* E-mail:<forcemz@outlook.com>
* @2015.25
**********************************************************************************************************/
#ifndef PHOENIX_EDITOR_MEMORY_FILEMODEL_H
#define PHOENIX_EDITOR_MEMORY_FILEMODEL_H
#include <stddef.h>
#include "StorageFile.h"
#include <vector>

#define  NewLine_WithCR  0x0d
#define  NewLine_WithCRLF 0x0d0a
#define  NewLine_WithLF 0x0a

typedef struct MmTextLineW__{
    wchar_t *start;
    size_t len;
}MmTextLineW;

typedef struct MmTextLineA__{
   char *start;
   size_t len;
}MmTextLineA;


typedef struct LineLinkTags{
   void *start;
   size_t dataSize;
   unsigned short newLine;
   LineLinkTags *Pre;
   LineLinkTags *Next;
}LineLink;

/// load memory begin LineLink *head=(LineLink*)malloc(sizeof(LineLink));..head->start=mstart;

#ifdef UNICODE
#define MmTextLine MmTextLineW
#else
#define MmTextLine MmTextLineA
#endif

#ifdef __cpluplus
class TextModelDocument{
private:
  LineLink linelink;
  std::map<unsigned,StorageFile *> storeMap;
  bool ParseStorageFile();
public:
  TextModelDocument();
  StorageFile *GetStorageFileFormIndex(unsigned index);
};
#endif


#endif
