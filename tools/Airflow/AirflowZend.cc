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
#include <wchar.h>
#include <errno.h>
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
    BYTE buffer[8]={0};
    DWORD size;
    HANDLE hFile=CreateFileW(file,GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(hFile==INVALID_HANDLE_VALUE)
    {
        wprintf(L"cannot open file %ls\n",file);
        return -1;
    }
    if (!ReadFile( hFile, buffer, sizeof(buffer), &size, NULL ))
    {
        CloseHandle(hFile);
        return -2;
    }
    CloseHandle(hFile);
    if(memcmp(buffer,MSI_MAGIC,sizeof(MSI_MAGIC))==0)
    {
        return PM_MICROSOFT_INSTALLER_DB;
    }else if(memcmp(buffer,LZ_MAGIC,sizeof(LZ_MAGIC))==0)
    {
        return PM_MICROSOFT_CAB_LZ;
    }else if(memcmp(buffer,MSZIP_MAGIC,sizeof(MSZIP_MAGIC))==0)
    {
        return PM_MICROSOFT_CAB_MSZIP;
    }else if(memcmp(buffer,NTCAB_MAGIC,sizeof(NTCAB_MAGIC))==0)
    {
        return PM_MICROSOFT_CAB_NTCAB;
    }
    else if(memcmp(buffer,InstallShieldCAB,sizeof(InstallShieldCAB))==0){
        return PM_INSTALLSHIELD_CAB;
    }
    return PACKAGE_MAGIC_UNKNOWN;
}

class ConsoleInitializeEx{
private:
    bool isOpen;
public:
    ConsoleInitializeEx(){
    }
    bool Init(){
        BOOL bRet = TRUE;
        if (AttachConsole(ATTACH_PARENT_PROCESS)!=TRUE){
            bRet = AllocConsole();
        }
        if (bRet){
            FILE *in, *out, *err;
            auto er = freopen_s(&in, "CONIN$", "r+t", stdin);
            er = freopen_s(&out, "CONOUT$", "w+t", stdout);
            er = freopen_s(&err, "CONOUT$", "w", stderr);
            //SetConsoleOutputCP(CP_ACP);
            auto lcid = GetSystemDefaultLCID();
            wchar_t szBuf[80] = { 0 };
            LCIDToLocaleName(lcid, szBuf, LOCALE_NAME_MAX_LENGTH, LOCALE_ALLOW_NEUTRAL_NAMES);
            _wsetlocale(LC_ALL, szBuf);
            //setlocale(LC_ALL, "zh-CN");
            isOpen = true;
        }else{
            isOpen = false;
        }
        return isOpen;
    }
    ~ConsoleInitializeEx()
    {
        if(isOpen)
        {
            printf("Plase Input Enter...\n");
			getchar();
            fflush(stdout);
            fclose(stdout);
            fclose(stdin);
            fclose(stderr);
            FreeConsole();
        }
    }
};
bool StringFindSlash(const wchar_t *str)
{
    auto p=str;
    while(*p)
    {
        if(*p=='\\'||*p=='/')
            return false;
        p++;
    }
    return true;
}



bool WINAPI CheckPackageAfterLayout(wchar_t *szPackagePath,size_t pksize,wchar_t *szRecover,size_t resize)
{
    errno_t  err;
    wchar_t szbuffer[4096]={0};
    std::wstring str;
    if(GetCurrentDirectory(4096,szbuffer)==0)
        return false;
    if((err=_waccess_s(const_cast<const wchar_t *>(szPackagePath),04))!=0){
        if(err!=ENOENT){
            std::wcout<<L"Check File Access Failed: "<<szPackagePath<<L"\nError Code:"<<err<<std::endl;
            return false;
        }
        if(StringFindSlash(const_cast<const wchar_t*>(szPackagePath)))
        {
            std::wcout<<L"Check File Access Failed: "<<szPackagePath<<L"\nError Code:"<<err<<std::endl;
            return false;
        }
        str=szbuffer;
        str+=L"\\";
        str+=szPackagePath;
        if((err=_waccess_s(str.c_str(),04))!=0)
        {
            std::wcout<<L"Check File Access Failed: "<<szPackagePath<<L"\nError Code:"<<err<<std::endl;
            return false;
        }else{
            wcscpy_s(szPackagePath,pksize,str.c_str());
            return true;
        }
    }
    if(_waccess(const_cast<const wchar_t *>(szRecover),04)==0)
        return true;
    if(!StringFindSlash(const_cast<const wchar_t *>(szRecover)))
    {
        if(CreateDirectory(const_cast<const wchar_t *>(szRecover),NULL)){
            wcscpy_s(szRecover,resize,str.c_str());
            return true;
        }
        else{
            std::wcout<<L"CreateDirectory Failed: "<<szRecover<<L"\nError Code:"<<GetLastError()<<std::endl;
            return false;
        }
    }
    str=szbuffer;
    str+=L"\\";
    str+=szRecover;
    if((err=_waccess_s(str.c_str(),04))!=0)
    {
        if(err!=ENOENT)
            return false;
        if(CreateDirectory(str.c_str(),NULL)){
            wcscpy_s(szRecover,resize,str.c_str());
            return true;
        }
        else{
            std::wcout<<L"CreateDirectory Failed: "<<str.c_str()<<L"\nError Code:"<<GetLastError()<<std::endl;
            return false;
        }
    }
    wcscpy_s(szRecover,resize,str.c_str());
    return true;
}

bool DoCheckerPackagePath(std::wstring &strPack,std::wstring &strDir)
{
    if(strPack.empty()||strDir.empty())
        return false;
    wchar_t szBuffer[4096]={0};
    std::wstring temp;
    if(GetCurrentDirectory(4096,szBuffer)==0)//why return false ,such as
        return false;
    if(_waccess_s(strPack.c_str(),04)!=0){
        if(StringFindSlash(strPack.c_str())){
            temp=std::wstring(szBuffer)+L"/"+strPack;
            if(_waccess_s(temp.c_str(),04)!=0)
            {
                return false;
            }
            strPack=temp;
        }else{
            return false;
        }
    }
    if(_waccess_s(strDir.c_str(),04)!=0){
        if(StringFindSlash(strDir.c_str())){
            temp=std::wstring(szBuffer)+L"/"+strDir;
            if(_waccess_s(temp.c_str(),04)!=0){
                if(CreateDirectory(temp.c_str(),NULL)){
                    //wcscpy_s(szRecover,resize,str.c_str());
                    strDir=temp;
                    return true;
                }else{
                    return false;
                }
            }
            strDir=temp;
        }
    }
    return true;
}

/*
#define FILE_COMPRESSION_NONE       0
#define FILE_COMPRESSION_WINLZA     1
#define FILE_COMPRESSION_MSZIP      2
#define FILE_COMPRESSION_NTCAB      3
*/

static RecoverRoute routeList[]={
    { PACKAGE_MAGIC_UNKNOWN,nullptr },
    { PM_MICROSOFT_INSTALLER_DB,RecoverInstallerPackage},
    { PM_MICROSOFT_CAB_LZ,RecoverCABPackage},
    { PM_MICROSOFT_CAB_MSZIP,RecoverCABPackage},
    { PM_MICROSOFT_CAB_NTCAB,RecoverCABPackage},
    { PM_INSTALLSHIELD_CAB,nullptr},
};

UINT WINAPI RecoverActionExectue(int magic,const wchar_t *rawin,const wchar_t *reout)
{
    for(auto &i:routeList)
    {
        if(i.reId==magic)
        {
            if(i.action!=nullptr){
                return i.action(rawin,reout);
            }else{
                return 1;
            }
        }
    }
    return 1;
}

//////when Airflow no UI,this call will run as
DWORD WINAPI AirflowZendMethodNonUI(AirflowStructure &airflowst)
{
    ConsoleInitializeEx con;
	if (!con.Init())
		return 2;///Console Initialize failed
    if(airflowst.cmdMode==CMD_PRINT_VERSION)
    {
        std::cout<<"Airflow Recover Windows Installer and Update Package File"<<std::endl;
        std::wcout<<AIRFLOW_VERSION_MARK<<std::endl;
        return 0;
    }else if(airflowst.cmdMode==CMD_PRINT_USAGE)
    {
		//wprintf(AIRFLOW_USAGE_STRING);
		//WriteConsoleOutputW()
        std::wcout<<AIRFLOW_USAGE_STRING<<std::endl;
        return 0;
    }
    if(airflowst.rawfile.empty())
    {
        std::wcout<<L"Please Input Your Package File: ";
        std::wcin>>airflowst.rawfile;
        //std::cout<<std::endl;
    }
    if(airflowst.outdir.empty())
    {
        std::wcout<<L"Please Input Your Recover Folder: ";
        std::wcin>>airflowst.outdir;
        //std::cout<<std::endl;
    }
    if(!DoCheckerPackagePath(airflowst.rawfile,airflowst.outdir)){
        std::wcout<<L"Do Check Raw Package and out Dir Failed."<<std::endl;
        return 2;
    }
    auto type=FindPackageMagic(airflowst.rawfile.c_str());
    RecoverActionExectue(type, airflowst.rawfile.c_str(), airflowst.outdir.c_str());
    return 0;
}

/////This is Call New Thread
DWORD WINAPI AirflowZendMethod(LPVOID lParam)
{
    if(!lParam)
        return 1;
    auto data=static_cast<AirflowTaskData *>(lParam);
    ///MessageBoxW(data->hWnd,L"AirflowZendMethod",data->rawfile.c_str(),MB_OK);
    auto type=FindPackageMagic(data->rawfile.c_str());
    RecoverActionExectue(type, data->rawfile.c_str(), data->outdir.c_str());
    SendMessageW(data->hWnd,data->uMsgid,0,0);
    delete data;
    return 0;
}
