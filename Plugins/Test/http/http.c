#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef int(*ReceiveResponeCallBack)(char *p,size_t buffer,void* t);
bool StandardRequest(const char *ua,
    const char *host,
    unsigned method,
    const char *url,
    bool useSSL,
    ReceiveResponeCallBack recallback,
    void *dataPtr);

int CallBackFun(char *p,size_t buffer,void *Ptr)
{
	printf("CallBackFun Get Datas:\n%s\n",p);
	//printf("%d",Ptr);
	return 0;
}
	
	
int main()
{
	int szCall=0;
	if(StandardRequest("Sq/5.0","stackoverflow.com",0,"/questions",false,CallBackFun,&szCall))
	{
		printf("\n\nStandardRequest Call Success!\n");
		printf("This Function Call Times: %d Pointer:%d",szCall,&szCall);
	}
	return 0;
}