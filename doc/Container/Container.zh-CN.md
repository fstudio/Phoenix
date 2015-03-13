#Phoenix 插件容器介绍


###1.启动低完整性进程
[强制完整性控制](http://zh.wikipedia.org/zh-cn/%E5%BC%BA%E5%88%B6%E5%AE%8C%E6%95%B4%E6%80%A7%E6%8E%A7%E5%88%B6)（英语：Mandatory Integrity Control）是一个在微软Windows操作系统中从Windows Vista开始引入，并沿用到后续版本系统的核心安全功能。强制完整性控制通过完整性级别标签来为运行于同一登录会话的进程提供隔离。此机制的目的是在一个潜在不可信的上下文（与同一账户下运行的其他较为可信的上下文相比）中选择性地限制特定进程和软件组件的访问权限。   
Windows Vista 定义了四个完整性级别:
>低 (SID: S-1-16-4096)   
>中 (SID: S-1-16-8192)   
>高 (SID: S-1-16-12288)  
>系統 (SID: S-1-16-16384)   

利用这一特性，我们可以使用低级别权限启动一个进程:

```C++
#include <Windows.h>
#include <Sddl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wchar.h>
#include <iostream>


#pragma comment(lib,"kernel32")
#pragma comment(lib,"Advapi32")
#pragma comment(lib,"user32")

BOOL WINAPI CreateLowLevelProcess(LPCWSTR lpCmdLine) {
  BOOL b;
  HANDLE hToken;
  HANDLE hNewToken;
  // PWSTR szProcessName = L"LowClient";
  PWSTR szIntegritySid = L"S-1-16-4096";
  PSID pIntegritySid = NULL;
  TOKEN_MANDATORY_LABEL TIL = {0};
  PROCESS_INFORMATION ProcInfo = {0};
  STARTUPINFOW StartupInfo = {0};
  StartupInfo.cb=sizeof(STARTUPINFOW);
  ULONG ExitCode = 0;

  b = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
  if(!b)
	  return FALSE;
  b = DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation,
                       TokenPrimary, &hNewToken);
  b = ConvertStringSidToSidW(szIntegritySid, &pIntegritySid);
  TIL.Label.Attributes = SE_GROUP_INTEGRITY;
  TIL.Label.Sid = pIntegritySid;

  // Set process integrity levels
  b = SetTokenInformation(hNewToken, TokenIntegrityLevel, &TIL,
                          sizeof(TOKEN_MANDATORY_LABEL) +
                              GetLengthSid(pIntegritySid));

  // Set process UI privilege level
  /*b = SetTokenInformation(hNewToken, TokenIntegrityLevel,
  &TIL, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(pIntegritySid)); */
  wchar_t *lpCmdLineT = _wcsdup(lpCmdLine);
  // To create a new low-integrity processes
  b = CreateProcessAsUserW(hNewToken, NULL, lpCmdLineT, NULL, NULL, FALSE, 0,
                          NULL, NULL, &StartupInfo, &ProcInfo);
  LocalFree(pIntegritySid);
  free(lpCmdLineT);
  return b;
}

int wmain(int argc,wchar_t *argv[])
{
	if(argc>=2)
	{
		std::wcout<<L"Start LowLevel App: "<<argv[1]<<L"\t Return Code[BOOL]: "<<CreateLowLevelProcess(argv[1])<<std::endl;
	}
	return 0;
}

```
第一步获得当前进程的Token,然后使用这个令牌创建一个新的令牌，由SID "S-1-16-4096"得到一个SID指针，将SID指针添加到TOKEN_MANDATORY_LABEL结构中，而后用SetTokenInformation将令牌与
完整性级别结合在一起，最后使用CreateProcessAsUser创建进程。通过完整性级别启动的进程是没有多少权限的，譬如打开一个记事本，新建一个文件另存为，基本上都无法写入。
使用Process Explorer可以查看启动进程的权限属性。
![LowLevelProperty](./Images/LowLevel.png)
标准权限的进程通常如下：
![NonLowLevelProperty](./Images/NonLowLevel.png)
实际上，光从属性上看两者之间并没有明显的差别
当低完整性进程对目录进行写入时，出现下图所示：
![Sava](./Images/LowLevelSava.png)


###2.UAC降权


####2.1计划任务降权的特例
通过计划任务降权在UAC开启的系统上基本上都会成功，但是，如果用户账户是内置的管理员账户，也就是Administrator，并且开启了**[对内置管理员使用批准模式](https://technet.microsoft.com/zh-cn/library/dd834795.aspx)**,那么上述的通过计划任务降权通常会失败，但是官方的任务管理器能够成功的降权，无论是[Process Explorer](http://www.sysinternals.com/)，还是[Process Hacker](http://processhacker.sourceforge.net/)都降权失败，即依然运行的是管理员权限的程序。当然，使用CreateProcessAsUser或者CreateProcessWithTokenW除外。
如果你的Shell没有被异常终止，也就是Explorer作为桌面启动的实例以标准权限运行着。


###3.使用AppContainer运行程序




###备注
开启 对内置管理员的批准模式
>运行（Win+R）输入"gpedit.msc",打开组策略编辑器，依次展开“计算机配置”里面的“Windows设置”，然后是“安全设置”，再就是“本地策略”里面的“安全选项”，在右边查找一项策略：“用户帐户控制: 用于内置管理员账户的管理员批准模式”，双击打开更改为“已启用”。