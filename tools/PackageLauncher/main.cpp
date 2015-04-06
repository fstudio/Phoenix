/*********************************************************************************************************
*   Phoneix Plugin Simple Launcher Host
*   Note: Launcher Main
*   Date: 2015.01.12
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Windows.h>
#include <libWrapper.h>

#ifdef _WIN64
#pragma comment(lib,"libtcc32.lib")
#else
#pragma comment(lib,"libtcc64.lib")
#endif

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
    CompilerStatus *s=CompilerNew();
    if(s==nullptr)
        return -1;
    CompilerDelete(s);
    return 0;
}


int main(int argc,const char** argv)
{
    return 0;
}
