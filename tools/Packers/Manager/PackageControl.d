/*********************************************************************************************************
* PackageControl.d
* Note: Phoenix Packers Manager PackageControl
* Data: 2015.05.02
* E-mail:<forcemz@outlook.com>
* Author: Force Charlie
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
import std.c.stdio

void PrintVersion()
{
    ///
    writeln("1.0.0.1");
}

void Usage()
{
    ////
}

int main(string[] args)
{
    bool ver;
    bool help;
    auto helpInformation=getopt(
        args,
        "version",&ver,
        "help",&help);
    if(ver){
        PrintVersion();
        return 0;
    }
    if(help)
    {
        Usage();
        return 0;
    }
    return 0;
}
