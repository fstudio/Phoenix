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

bool StandardURLResolve(const char *uri,char *scheme,char *host,char *path,unsigned *ports);	
	
int CallBackFun(char *p,size_t buffer,void *Ptr)
{
	//printf("CallBackFun Get Datas:\n%s\n",p);
	Index *id=(Index *)Ptr;
	id->index++;
	//printf("Value:%d Pointer:%d\n",*Ptr,Ptr);
	return 0;
}

void ParserURL()
{
	char url[1024]="https://github.com/fstudio/Phoenix/as";
	char sc[100]={0};
	char host[256]={0};
	char path[2049]={0};
	unsigned port=0;
	StandardURLResolve(url,sc,host,path,&port);
	printf("StandardURLResolve \nScheme:\t%s\nHost:\t%s\nPath:\t%s\nPorts:\t%d\n",sc,host,path,port);
}	
	
int main()
{
	ParserURL();
	Index id={0};
	if(StandardRequest("Sq/5.0","stackoverflow.com",0,"/questions",false,CallBackFun,&id))
	{
		printf("\n\nStandardRequest Call Success!\n");
		printf("This Function Call Times: %d Pointer:%d",id.index,&id);
	}
	return 0;
}