#Phoenix Package Runtime
Phoenix is a Powerful Editor,This Plugin-System use ANSI-C   
Some one can use Tiny C Compiler run or compiler Plugin source code.
####PackageRuntime
Package Runtime export function :
```def
LIBRARY PackageRuntime.dll

EXPORTS
Base64Decode
Base64Encode
Base64StringFree
CharlieUUIDFormatFormString
CharlieUUIDFormatToString
CharlieUUIDIsEquals
CharlieUUIDRandom
ComperssFolderFiles
ComponentInitialize
ComponentInitializeEx
ComponentUnInitialze
GCAlloc
GCDestory
GCInitialize
GCMalloc
GetAttribute
GetElementText
GetForeachElementNamespaceText
GetForeachNamespaceAttribute
JSONResolveDelete
JSONResolveGetKV
JSONResolveNew
JSONResolveNewEx
PackageRuntimeStandardRequest
ReferenceDestory
ReferenceInitialize
ReferencePush
RequestBufferFree
RequestCreateNew
RequestFree
SendRequest
SetUserAgent
StandardRequest
StandardURLResolve
URIGetPortFromSchemes
XmlResolveDelete
XmlResolveLoader
XmlResolveNew
getopt
getopt_long
getopt_long_only
md5bin
optarg
optind
optreset
```

#####JSON

#####HTTP

#####UUID 
PackageRuntime UUID Features:
Get uuid from a hex-string: *CharlieUUIDFormatFormString*      
Format uuid to a hex-string: *CharlieUUIDFormatToString*   
Equals two UUID: *CharlieUUIDIsEquals*    
Random uuid: *CharlieUUIDRandom*  

```c


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <Runtime/UUID.h>

int main()
{
  CharlieUUID uuid;
  char sz[UUID_STRING_MAX_LENGTH]={0};
  CharlieUUIDRandom(&uuid);
  CharlieUUIDFormatToString(&uuid,sz);
  printf("UUID:%s",sz);
  return 0;
}
```

#####Base64
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Runtime/Base64.h>


int main()
{
	char str[]="This is Base64 Encode and Decode Info\0";
	char bs[512]={0};
	size_t out=0;
	char *p=NULL;
	if((p=Base64Encode(str,strlen(str),&out))!=NULL)
	{
		printf("Base64Encode: %s Length:%d\n",p,out);
		snprintf(bs,511,"%s",p);
		Base64StringFree(p);
		if((p=Base64Decode(bs,strlen(bs),&out))!=NULL)
		{
			printf("Base64Decode: %s Length:%d\n",p,out);
			Base64StringFree(p);
		}
	}
	return 0;
}
```

####GC


####ZIP
