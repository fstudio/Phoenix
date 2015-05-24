/*********************************************************************************************************
* PhoenixStandardIO.cpp
* Note: Phoenix Standard IO
* Date: @2015.03
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Header.hpp"
#include <stdio.h>

class StandardIO{
private:
    HANDLE hStd;
public:
    StandardIO();
    ~StandardIO();
    bool Input();
    bool Output();
};

BOOL StandardMain(int Argc,wchar_t **Argv)
{
    //
    BOOL bRet=TRUE;
    if((bRet=AttachConsole(ATTACH_PARENT_PROCESS))!=TRUE){
        return bRet;
    }
    freopen("CONIN$" , "r+t" , stdin);
    freopen("CONOUT$" , "w+t" , stdout);
    freopen("CONOUT$", "w", stderr);
    return bRet;
}

BOOL CloseStandardIO()
{
    fclose(stdout);
    fclose(stdin);
    fclose(stderr);
    return TRUE;
}

bool CreateConsoleWindow()
{
    if(AllocConsole()!=TRUE)
        return false;
    return true;
}
