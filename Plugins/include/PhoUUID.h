#ifndef PHO_PLUGINS_UUID_H
#define PHO_PLUGINS_UUID_H

#include <stdint.h>

typedef struct PhoUUID__{
   uint32_t Data1;
   uint16_t Data2;
   uint16_t Data3
   uint8_t Data4[8];
}PhoUUID;



#endif
