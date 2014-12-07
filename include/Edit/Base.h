//
#ifndef PHOENIX_EDIT_BASE_H
#define PHOENIX_EDIT_BASE_H
#include <stddef.h>

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
