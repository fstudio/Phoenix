

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct CharlieUUID{
   uint32_t Data1;
   uint16_t Data2;
   uint16_t Data3;
   uint8_t Data4[8];
}CharlieUUID;

#define UUID_STRING_MAX_LENGTH  37

int CharlieUUIDRandom(CharlieUUID *uuid);
int CharlieUUIDFormatFormString(const char *uuidString,CharlieUUID *uuid);
int CharlieUUIDFormatToString(const CharlieUUID *uuid,char *stringBuffer);
bool CharlieUUIDIsEquals(const CharlieUUID *uuid1,const CharlieUUID *uuid2);


int main()
{
  CharlieUUID uuid;
  char sz[UUID_STRING_MAX_LENGTH]={0};
  CharlieUUIDRandom(&uuid);
  CharlieUUIDFormatToString(&uuid,sz);
  printf("UUID:%s",sz);
  return 0;
}