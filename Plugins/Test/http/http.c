#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct Index__{
	int index;
}Index;

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
	Index *id=(Index *)Ptr;
	id->index++;
	printf("Value:%d Pointer:%d\n",*Ptr,Ptr);
	return 0;
}

	
	
int main()
{
	Index id={0};
	if(StandardRequest("Sq/5.0","stackoverflow.com",0,"/questions",false,CallBackFun,&id))
	{
		printf("\n\nStandardRequest Call Success!\n");
		printf("This Function Call Times: %d Pointer:%d",id.index,&id);
	}
	return 0;
}