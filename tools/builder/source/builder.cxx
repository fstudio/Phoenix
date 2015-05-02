/*********************************************************************************************************
*   Phoenix Package Builder tools
*   Note: builder.cc
*   Data: 2015.01.18
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <iostream>
#include <string>
#include <Arguments/Arguments.hpp>
#include <gflags/gflags.h>

int main(int argc,char *argv[])
{
    Arguments Args=Arguments::Main(argc,argv);
    google::ParseCommandLineFlags(&Args.argc(),&Ars.argv(),true);
    return 0;
}

