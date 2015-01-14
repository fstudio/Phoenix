/*********************************************************************************************************
*   Phoneix Plugin Runtime
*   Note: UUID
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Runtime/UUID.h>
#include <objbase.h>

static const BYTE hex2bin[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* 0x00 */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* 0x10 */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* 0x20 */
    0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,        /* 0x30 */
    0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,  /* 0x40 */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        /* 0x50 */
    0,10,11,12,13,14,15                     /* 0x60 */
};


PKGEXTERN int CharlieUUIDRandom(CharlieUUID *uuid)
{
    if(uuid==NULL)
        return -1;
    GUID guid;
    ZeroMemory(&guid,sizeof(GUID));
    if(CoCreateGuid(&guid)!=S_OK)
        return -1;
    memcpy(uuid,&guid,sizeof(GUID));
    return 0;
}
PKGEXTERN int CharlieUUIDFormatFormString(const char *s,CharlieUUID *uuid)
{
    if(uuid==NULL||s==NULL)
        return -1;
    if ((s[8]!='-') || (s[13]!='-') || (s[18]!='-') || (s[23]!='-'))
        return 1;
    for (i=0; i<36; i++)
    {
        if ((i == 8)||(i == 13)||(i == 18)||(i == 23)) continue;
        if (s[i] > 'f' || (!hex2bin[s[i]] && s[i] != '0')) return 2;
    }
    uuid->Data1 = (hex2bin[s[0]] << 28 | hex2bin[s[1]] << 24 | hex2bin[s[2]] << 20 | hex2bin[s[3]] << 16 |
                   hex2bin[s[4]] << 12 | hex2bin[s[5]]  << 8 | hex2bin[s[6]]  << 4 | hex2bin[s[7]]);
    uuid->Data2 =  hex2bin[s[9]] << 12 | hex2bin[s[10]] << 8 | hex2bin[s[11]] << 4 | hex2bin[s[12]];
    uuid->Data3 = hex2bin[s[14]] << 12 | hex2bin[s[15]] << 8 | hex2bin[s[16]] << 4 | hex2bin[s[17]];

    /* these are just sequential bytes */
    uuid->Data4[0] = hex2bin[s[19]] << 4 | hex2bin[s[20]];
    uuid->Data4[1] = hex2bin[s[21]] << 4 | hex2bin[s[22]];
    uuid->Data4[2] = hex2bin[s[24]] << 4 | hex2bin[s[25]];
    uuid->Data4[3] = hex2bin[s[26]] << 4 | hex2bin[s[27]];
    uuid->Data4[4] = hex2bin[s[28]] << 4 | hex2bin[s[29]];
    uuid->Data4[5] = hex2bin[s[30]] << 4 | hex2bin[s[31]];
    uuid->Data4[6] = hex2bin[s[32]] << 4 | hex2bin[s[33]];
    uuid->Data4[7] = hex2bin[s[34]] << 4 | hex2bin[s[35]];
    return 0;
}
PKGEXTERN int CharlieUUIDFormatToString(const CharlieUUID *uuid,char *stringBuffer)
{
    if(uuid==NULL||stringBuffer==NULL)
        return -1;
    sprintf_s(stringBuffer,UUID_STRING_MAX_LENGTH,"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
        uuid->Data1,
        uuid->Data2,
        uuid->Data3,
        uuid->Data4[0],
        uuid->Data4[1],
        uuid->Data4[2],
        uuid->Data4[3],
        uuid->Data4[4],
        uuid->Data4[5],
        uuid->Data4[6],
        uuid->Data4[7])
    return 0;
}

PKGEXTERN bool CharlieUUIDIsEquals(const CharlieUUID *uuid1,const CharlieUUID *uuid2)
{
    if(uuid1==NULL&&uuid2==NULL)
        return true;
    return  (memcmp(uuid1,uuid2,sizeof(CharlieUUID))==0);
}
