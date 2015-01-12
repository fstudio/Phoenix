#include <iostream>
#include <stdlib.h>
#include <string>
#include "libtcc.h"


int Launcher(const char* source,const char* incdir,const char* libdir,const char* addlib,bool isScriptModule)
{
	TCCState *s=tcc_new();
	if(s==nullptr)
		return -1;
	tcc_delete(s);
	return 0;
}


int main(int argc,const char** argv)
{
	return 0;
}