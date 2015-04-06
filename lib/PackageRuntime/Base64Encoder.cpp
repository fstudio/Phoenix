/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: Base64
*   Date: 2015.02.07
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <cstdio>
#include <cstring>
#include <Runtime/Base64.h>
static bool IsBase64(char c)
{
    if((c>='A'&&c<='Z')||(c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='+'||c=='/'||c=='=')
        return true;
    return false;
}

inline char CharEncode(char c)
{
    if(c<26)
        return 'A'+c;
    if(c<52)
        return 'a'+(c-26);
    if(c<62)
        return '0'+(c-52);
    if(c==62)
        return '+';
    return '/';
}

unsigned char CharDecode(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 26;
    if (c >= '0' && c <= '9')
        return c - '0' + 52;
    if (c == '+')
        return 62;
    return 63;
}

extern "C" PKGEXTERN char *Base64Encode(const char* raw,size_t len,size_t *LengthOfOut)
{
    size_t linelength=0;
    *LengthOfOut=0;
    size_t outlength=0;
    if(raw==nullptr||len==0)
        return nullptr;
    char *retval=new char[len*2];
    const char *crlf="\n";
    auto crlflen=strlen(crlf);
    size_t maxlinelength=76;
    for(size_t i=0;i<len;i+=3)
    {
        unsigned char b1, b2, b3, b4, b5, b6, b7;
        b1 = raw[i];
        if (i+1 < len){
            b2 = raw[i+1];
        }else{
            b2=0;
        }
        if (i+2 < len){
            b3 = raw[i+2];
        }else{
            b3=0;
        }
        b4 = b1>>2;
        b5 = ((b1 & 0x3)<<4)|( b2>>4 );
        b6 = ((b2 & 0xf)<<2)|( b3>>6 );
        b7 = b3 & 0x3f;

        retval[outlength++] = CharEncode(b4);
        linelength++;

        retval[outlength++] = CharEncode(b5);
        linelength++;
        if (i+1 < len){
            retval[outlength++]= CharEncode(b6);
            linelength++;
        }else{
            retval[outlength++]= '=';
            linelength++;
        }
        if (i+2<len)
        {
            retval[outlength++]= CharEncode(b7);
            linelength++;
        }else{
            retval[outlength++]= '=';
            linelength++;
        }
        if (maxlinelength != 0 && linelength >= maxlinelength){
            for(int y=0; y< crlflen; y++){
                retval[outlength++]= crlf[y];
            }
            linelength=0;
        }
      };
      retval[outlength]='\0';
      *LengthOfOut=outlength;
      return retval;
}

extern "C" PKGEXTERN char *Base64Decode(const char *data,size_t len,size_t *LengthOfOut)
{
    if(data == nullptr || len == 0){
        *LengthOfOut=0;
        return nullptr;
    }
    size_t outlength=0;
    size_t rawlength=0;
    char *outbuffer=new char[len];
    for (size_t j=0;j < len; j++){
        if (IsBase64(data[j]))
            outbuffer[rawlength++]= data[j];
    }
    if (rawlength == 0 || len == 0){
        delete [] outbuffer;
        return nullptr;
    }
    for (size_t i=0; i<rawlength; i+=4){
        char c1 = outbuffer[i];
        char c2='A',c3='A',c4='A';
        if (i+1 < rawlength){
            c2 = outbuffer[i+1];
        }
        if (i+2 < rawlength){
            c3 = outbuffer[i+2];
        }
        if (i+3 < rawlength){
            c4 = outbuffer[i+3];
        }
        unsigned char b1,b2,b3,b4;
        b1 = CharDecode(c1);
        b2 = CharDecode(c2);
        b3 = CharDecode(c3);
        b4 = CharDecode(c4);
        outbuffer[outlength]=( (b1<<2)|(b2>>4) );
        outlength++;
        if (c3 != '='){
            outbuffer[outlength]=( ((b2&0xf)<<4)|(b3>>2) );
            outlength++;
        }
        if (c4 != '='){
            outbuffer[outlength]=( ((b3&0x3)<<6)|b4 );
            outlength++;
        }
    }
    outbuffer[outlength]='\0';
    *LengthOfOut=outlength;
    return outbuffer;
}

extern "C" PKGEXTERN void Base64StringFree(char* p)
{
    if(p)
        delete []p;
}