////Container
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <Shlwapi.h>

int UACLimit()
{
 return 0;	
}

int ContainerInstance(std::wstring relFile,std::wstring cmdArgs)
{
	if(PathFileExistsW(relFile)!=TRUE)
		return -1;
	return 0;
}


int ContainerInit()
{
	return 0;
}

///Windows JobObject sample.
///SetInformationJobObject

int WINAPI wWinMain(HINSTANCE,HINSTANCE,PWSTR,int)
{
	return 0;
}