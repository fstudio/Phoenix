/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: Launcher Main
*   Data: 2015.01.12
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include "libtcc.h"

bool GetDefaultSearchFolder(char *outdir)
{
    return false;
}

bool GetDefualtLibraryPath(char *libdir)
{
    return false;
}

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