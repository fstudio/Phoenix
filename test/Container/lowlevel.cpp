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

