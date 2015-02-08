////This Debug Trace Model

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

static FILE *Iofp=nullptr;

static bool GetDefaultLogIOFile()
{
	char temp[4096]={0};
	if(GetTempPathA(256,temp)==0)
		return false;/// This Function invoke failed.
#if defined(_MSC_VER)&& _MSC_VER>=1400
	strcat_s(temp,4096,"/Package-Runtime-Debug-S1-Info.log");
	if(fopen_s(&Iofp,temp,"at+")!=0)
		return false;
#else
	strcat(temp,"/Package-Runtime-Debug-S1-Info.log");
    if((Iofp=fopen(temp,"at+"))==nullptr)
		return false;
#endif
	return true;
}

extern "C" bool InitializeDebugIO()
{
	return GetDefaultLogIOFile();
}

extern "C" void DestoryDebugIO()
{
	if(Iofp)
		fclose(Iofp);
}
 
extern "C" void TRACE(FILE *fp,const char* format,...)
{
  if(fp!=nullptr)
  {
    int ret;
    va_list ap;
    va_start(ap, format);
    ret = vfprintf(fp, format, ap);
    va_end(ap);
  }
}
