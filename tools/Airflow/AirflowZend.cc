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

/**
MSI:
1.D0-CF-11-E0-A1-B1-1A-E1-00-00
2.D0-CF-11-E0-A1-B1-1A-E1-00-00
3.D0-CF-11-E0-A1-B1-1A-E1-00-00

MSU:
1.4D-53-43-46-00-00-00-00-34-A6
2.4D-53-43-46-00-00-00-00-49-7E
3.4D-53-43-46-00-00-00-00-5A-42
4.4D-53-43-46-00-00-00-00-32-6B

MSP:
1.D0-CF-11-E0-A1-B1-1A-E1-00-00
2.D0-CF-11-E0-A1-B1-1A-E1-00-00
3.D0-CF-11-E0-A1-B1-1A-E1-00-00

CAB:
1.4D-53-43-46-00-00-00-00-F9-05
2.4D-53-43-46-00-00-00-00-74-C7
3.4D-53-43-46-00-00-00-00-8E-0F

msi and msp format Consistent
msu and cab format Consistent

*/
#define MAGIC_SIZE 8
const unsigned char MIS_MAGIC[]={0xD0,0xCF,0x11,0xE0,0xA1,0xB1,0x1A,0xE1};
const unsigned char CAB_MAGIC[]={0x4D,0x53,0x43,0x46,0x00,0x00,0x00,0x00};


int FindPackageMagic(const wchar_t *file)
{
    char buffer[20]={0};
    FILE *fp=nullptr;
    if(_wfopen_s(&fp,file,L"rb")!=0)
        return -1;
    if(fread_s(buffer,20,1,20,fp)<0)
    {
        fclose(fp);
        return -2;
    }
    fclose(fp);
    const unsigned char *p=reinterpret_cast<const unsigned char*>(buffer);
    if(memcmp(p,MIS_MAGIC,8)==0)
    {

    }else if(memcmp(p,CAB_MAGIC,8)==0)
    {

    }else{
        /// Unknown File format
    }
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