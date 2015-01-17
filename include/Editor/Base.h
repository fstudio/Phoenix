//
#ifndef PHOENIX_EDIT_BASE_H
#define PHOENIX_EDIT_BASE_H
#include <stddef.h>

#define  NEWLINE_CR  0x0d
#define  NEWLINE_CRLF 0x0d0a
#define  NEWLINE_LF 0x0a

typedef struct PhoTextLineW__{
    wchar_t *start;
    size_t len;
}PhoTextLineW;

typedef struct PhoTextLineA__{
   char *start;
   size_t len;
}PhoTextLineA;


typedef struct LineLinkTags{
   void *start;
   size_t dataSize;
   unsigned short newLine;
   LineLinkTags *Pre;
   LineLinkTags *Next;
}LineLink;

/// load memory begin LineLink *head=(LineLink*)malloc(sizeof(LineLink));..head->start=mstart;

#ifdef UNICODE
#define PhoTextLine PhoTextLineW
#else
#define PhoTextLine PhoTextLineA
#endif

#ifdef __cpluplus
class TextDocument{
private:
    LineLink linelink;
    int ParsePhyMemoryFile();
public:
    TextDocument();
};
#endif


#endif
