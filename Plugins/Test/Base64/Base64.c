#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *Base64Encode(const char* raw,size_t len,size_t *outlen);
char *Base64Decode(const char *data,size_t len,size_t *outlen);
void Base64StringFree(char* p);


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