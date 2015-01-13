/*********************************************************************************************************
*   Phoneix Plugin Runtime
*   Note: PackageInitialize.cpp This File is Single-Exe Entry .
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <memory.h>
int PackageInitialize(int Argc,char **Argv);

int main(int argc,char **argv)
{
    ///Resource Allocate.
    int ret=PackageInitialize(argc,argv);
    ///Resource Free
    return ret;
}
