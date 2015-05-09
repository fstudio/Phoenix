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
#include <iostream>
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

Notice: this cab is NTCAB not other cab format


*/


int FindPackageMagic(const wchar_t *file)
{
    static const BYTE MSI_MAGIC[]={0xD0,0xCF,0x11,0xE0,0xA1,0xB1,0x1A,0xE1};
    static const BYTE LZ_MAGIC[] = { 0x53, 0x5a, 0x44, 0x44, 0x88, 0xf0, 0x27, 0x33 };
    static const BYTE MSZIP_MAGIC[] = { 0x4b, 0x57, 0x41, 0x4a };
    static const BYTE NTCAB_MAGIC[] = { 0x4d, 0x53, 0x43, 0x46 };
    static const BYTE InstallShieldCAB[]={'I','S','c'};
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
    const BYTE *p=reinterpret_cast<const BYTE*>(buffer);
    if(memcmp(p,MSI_MAGIC,8)==0)
    {
        return PM_MICROSOFT_INSTALLER_DB;
    }else if(memcmp(p,LZ_MAGIC,8)==0)
    {
        return PM_MICROSOFT_CAB_LZ;
    }else if(memcmp(p,MSZIP_MAGIC,4)==0)
    {
        return PM_MICROSOFT_CAB_MSZIP;
    }else if(memcmp(p,NTCAB_MAGIC,4)==0)
    {
        return PM_MICROSOFT_CAB_NTCAB;
    }
    else if(memcmp(p,InstallShieldCAB,3)==0){
        return PM_INSTALLSHIELD_CAB;
    }
    return PACKAGE_MAGIC_UNKNOWN;
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
    if(airflowst.cmdMode==CMD_PRINT_VERSION)
    {
        std::cout<<"Airflow 1.0.0.1"<<std::endl;
        return 0;
    }
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