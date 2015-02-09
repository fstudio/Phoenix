#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

char *PackageRuntimeStandardRequest(const char *ua,const char *host,unsigned method,const char *url,size_t *bufferSize,bool useSSL);
void RequestBufferFree(void *p);


int main()
{
	char *p=NULL;
	size_t bSize=0;
	if((p=PackageRuntimeStandardRequest("Sq/5.0","stackoverflow.com",0,"/questions",&bSize,false))!=NULL)
	{
		printf("Request BufferSize:%d Request Body:\n%s\nPointer: %d\n",bSize,p,p);
		RequestBufferFree(p);
	}
	return 0;
}