/*********************************************************************************************************
*   Phoneix Package Runtime
*   Note: PackageInitialize.c This File is Single-Exe Entry .
*   Data: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <memory.h>
#include <Runtime.h>
int PackageInitialize(int Argc,char **Argv);

int main(int argc,char **argv)
{
    ///Resource Allocate.
    if(!ComponentInitialize())
        return -1;
    int ret=PackageInitialize(argc,argv);
    ///Resource Free
    if(!ComponentUnInitialze())
        return -1;
    return ret;
}
