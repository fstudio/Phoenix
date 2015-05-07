/*********************************************************************************************************
* AirflowZend.cc
* Note: Phoenix Airflow tools
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Airflow.h"
#include <stdio.h>
#include <stdlib.h>

int FindPackageMagic(const wchar_t *file)
{
    return 0;
}

class ConsoleAttachEx{
private:
  bool isOpen;
public:
  ConsoleAttachEx()
  {
    if(AttachConsole(ATTACH_PARENT_PROCESS))
    {
      freopen("CONIN$" , "r+t" , stdin);
      freopen("CONOUT$" , "w+t" , stdout);
      freopen("CONOUT$", "w", stderr);
      isOpen=true;
    }else{
      isOpen=false;
    }
  }
  ~ConsoleAttachEx()
  {
    if(isOpen)
    {
      fclose(stdout);
      fclose(stdin);
      fclose(stderr);
      FreeConsole();
    }
  }
};

bool SendMessageEnter()
{
    return true;
}

//////when Airflow no UI,this call will run as
DWORD WINAPI AirflowZendMethodNonUI(AirflowStructure &airflowst)
{
    return 0;
}

/////This is Call New Thread
DWORD WINAPI AirflowZendMethod(LPVOID lParam)
{
    if(!lParam)
        return 1;
    auto data=static_cast<AirflowTaskData *>(lParam);
    return 0;
}