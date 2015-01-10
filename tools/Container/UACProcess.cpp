
#include "Precompiled.h"
#include <taskschd.h>
#include <comdef.h>
#include <Sddl.h>
#include <string.h>

//////////////////////////////////////////////////////////
// Release COM reasource
template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
  if (*ppInterfaceToRelease != nullptr) {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = nullptr;
  }
}
#ifndef ASSERT
#ifdef _DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#define ASSERT_HERE assert(FALSE)
#else // _DEBUG
#define ASSERT(x)
#define ASSERT_HERE
#endif //_DEBUG
#endif // ASSERT

#ifndef _tsizeof
#define _tsizeof(s) (sizeof(s) / sizeof(s[0]))
#endif //_tsizeof

#define DO(action)                                                             \
  if (FAILED( action )) {                                                        \
    ASSERT( FALSE );                                                             \
    goto ClenUp;                                                               \
  }

HRESULT WINAPI TaskUACRunNonElevated(LPCWSTR pszPath, LPCWSTR pszParameters,
                                     LPCWSTR pszDirectory) {
  // If Your User is Administrator (Windows Default) Task run dafault by
  // Administrator,So, user Explorer's Token <CreateProcessAsTokenW>
  // ITaskSettings3
  /**************************************************************************
  *  ITaskSettings3 Support Windows 8 or Later,This App Support Windows 7
  *  So Use ITaskSettings2
  **************************************************************************/
  // ITaskSettings2 iTask;

  HRESULT hr = S_OK;
  ITaskService *iTaskService = nullptr;
  ITaskFolder *iRootFolder = nullptr;
  ITaskDefinition *iTask = nullptr;
  IRegistrationInfo *iRegInfo = nullptr;
  IPrincipal *iPrin = nullptr;
  ITaskSettings *iSettings = nullptr;
  ITriggerCollection *iTriggerCollection = nullptr;
  ITrigger *iTrigger = nullptr;
  IRegistrationTrigger *iRegistrationTrigger = nullptr;
  IActionCollection *iActionCollection = nullptr;
  IAction *iAction = nullptr;
  IExecAction *iExecAction = nullptr;
  IRegisteredTask *iRegisteredTask = nullptr;

  LPCWSTR pszTaskName = L"Phoenix.Container-CreateNonElevatedProcess-Task-APIv1";

  DO(hr = CoCreateInstance(CLSID_TaskScheduler, nullptr, CLSCTX_INPROC_SERVER,IID_ITaskService, (void **)&iTaskService));
  //WCHAR szError=

  DO(iTaskService->Connect(_variant_t(), _variant_t(), _variant_t(), _variant_t()));

  DO(iTaskService->GetFolder(_bstr_t(L"\\"), &iRootFolder));
  iRootFolder->DeleteTask(_bstr_t(pszTaskName), 0);

  DO(iTaskService->NewTask(0, &iTask));

  DO(iTask->get_RegistrationInfo(&iRegInfo));

  DO(iRegInfo->put_Author(L"PhoenixContainerRunLimitUser"));

  DO(iTask->get_Principal(&iPrin));

  DO(iPrin->put_Id(_bstr_t(L"PhoenixContainerRunLimitUser_Principal")))

  DO(iPrin->put_LogonType(TASK_LOGON_INTERACTIVE_TOKEN))

  //  Run the task with the least privileges (LUA)
  DO(iPrin->put_RunLevel(TASK_RUNLEVEL_LUA))

  //  Create the settings for the task

  DO(iTask->get_Settings(&iSettings))

  //  Set setting values for the task.
  DO(iSettings->put_StartWhenAvailable(VARIANT_BOOL(true)))

  //  Get the trigger collection to insert the registration trigger.

  DO(iTask->get_Triggers(&iTriggerCollection))

  //  Add the registration trigger to the task.

  DO(iTriggerCollection->Create(TASK_TRIGGER_REGISTRATION, &iTrigger))

  DO(iTrigger->QueryInterface(IID_IRegistrationTrigger,
                              (void **)&iRegistrationTrigger))

  DO(iRegistrationTrigger->put_Id(
      _bstr_t(L"PhoenixContainerRunLimitUser_Trigger")))

  //  Define the delay for the registration trigger.
  DO(iRegistrationTrigger->put_Delay(L"PT0S")) // 0 second delay of execution;

  //  Add an Action to the task. This task will execute notepad.exe.

  //  Get the task action collection pointer.
  DO(iTask->get_Actions(&iActionCollection))

  //  Create the action, specifying that it is an executable action.

  DO(iActionCollection->Create(TASK_ACTION_EXEC, &iAction))

  //  QI for the executable task pointer.
  DO(iAction->QueryInterface(IID_IExecAction, (void **)&iExecAction))

  //  Set the path of the executable to notepad.exe.
  DO(iExecAction->put_Path(_bstr_t(pszPath)))

  if (pszParameters) {
    DO(iExecAction->put_Arguments(_bstr_t(pszParameters)))
  }

  if (pszDirectory) {
    DO(iExecAction->put_WorkingDirectory(_bstr_t(pszDirectory)))
  }

  //  Save the task in the root folder.

  DO(iRootFolder->RegisterTaskDefinition(
      _bstr_t(pszTaskName), iTask, TASK_CREATE_OR_UPDATE, _variant_t(),
      _variant_t(), TASK_LOGON_INTERACTIVE_TOKEN, _variant_t(L""),
      &iRegisteredTask));
  hr = S_OK;
  goto ClenUp;

ClenUp:
  SafeRelease(&iTaskService);
  SafeRelease(&iTask);
  SafeRelease(&iRootFolder);
  SafeRelease(&iRegInfo);
  SafeRelease(&iPrin);
  SafeRelease(&iRegistrationTrigger);
  SafeRelease(&iTriggerCollection);
  SafeRelease(&iTrigger);
  SafeRelease(&iActionCollection);
  SafeRelease(&iSettings);
  SafeRelease(&iAction);
  SafeRelease(&iExecAction);
  SafeRelease(&iRegisteredTask);
  return hr;
}
/*
* HRESULT WINAPI CreateProcessWithShellToken();
* @param:
*  exePath
*  cmdArgs
*  workdir
* startinfo
* processinfo
* @return Zero success
*/
HRESULT WINAPI
CreateProcessWithShellToken(LPCWSTR exePath, _In_ LPCWSTR cmdArgs,
                            _In_ LPCWSTR workDirectory, _In_ STARTUPINFOW &si,
                            _Inout_ PROCESS_INFORMATION &pi) {
  HANDLE hShellProcess = nullptr, hShellProcessToken = nullptr,
         hPrimaryToken = nullptr;
  HWND hwnd = nullptr;
  DWORD dwPID = 0;
  HRESULT hr = S_OK;
  BOOL ret = TRUE;
  DWORD dwLastErr;

  // Enable SeIncreaseQuotaPrivilege in this process.  (This won't work if
  // current process is not elevated.)
  HANDLE hProcessToken = nullptr;
  if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,
                        &hProcessToken)) {
    return HRESULT(1);
  } else {
    TOKEN_PRIVILEGES tkp;
    tkp.PrivilegeCount = 1;
    LookupPrivilegeValueW(nullptr, SE_INCREASE_QUOTA_NAME,
                          &tkp.Privileges[0].Luid);
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hProcessToken, FALSE, &tkp, 0, nullptr, nullptr);
    dwLastErr = GetLastError();
    CloseHandle(hProcessToken);
    if (ERROR_SUCCESS != dwLastErr) {
      return HRESULT(2);
    }
  }

  // Get an HWND representing the desktop shell.
  // CAVEATS:  This will fail if the shell is not running (crashed or
  // terminated), or the default shell has been
  // replaced with a custom shell.  This also won't return what you probably
  // want if Explorer has been terminated and
  // restarted elevated.
  hwnd = GetShellWindow();
  if (nullptr == hwnd) {
    return HRESULT(3);
  }

  GetWindowThreadProcessId(hwnd, &dwPID);
  if (0 == dwPID) {
    return HRESULT(4);
  }

  // Open the desktop shell process in order to query it (get the token)
  hShellProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPID);
  if (!hShellProcess) {
    dwLastErr = GetLastError();
    return HRESULT(5);
  }

  // From this point down, we have handles to close, so make sure to clean up.

  bool retval = false;
  // Get the process token of the desktop shell.
  ret = OpenProcessToken(hShellProcess, TOKEN_DUPLICATE, &hShellProcessToken);
  if (!ret) {
    dwLastErr = GetLastError();
    hr = HRESULT(6);
    goto cleanup;
  }

  // Duplicate the shell's process token to get a primary token.
  // Based on experimentation, this is the minimal set of rights required for
  // CreateProcessWithTokenW (contrary to current documentation).
  const DWORD dwTokenRights = TOKEN_QUERY | TOKEN_ASSIGN_PRIMARY |
                              TOKEN_DUPLICATE | TOKEN_ADJUST_DEFAULT |
                              TOKEN_ADJUST_SESSIONID;
  ret = DuplicateTokenEx(hShellProcessToken, dwTokenRights, nullptr,
                         SecurityImpersonation, TokenPrimary, &hPrimaryToken);
  if (!ret) {
    dwLastErr = GetLastError();
    hr = 7;
    goto cleanup;
  }
  // Start the target process with the new token.
  wchar_t *cmdArgsT = _wcsdup(cmdArgs);
  ret = CreateProcessWithTokenW(hPrimaryToken, 0, exePath, cmdArgsT, 0, nullptr,
                                workDirectory, &si, &pi);
  free(cmdArgsT);
  if (!ret) {
    dwLastErr = GetLastError();
    hr = 8;
    goto cleanup;
  }

  retval = true;

cleanup:
  // Clean up resources
  CloseHandle(hShellProcessToken);
  CloseHandle(hPrimaryToken);
  CloseHandle(hShellProcess);
  return hr;
}

BOOL WINAPI CreateLowLevelProcess(LPCWSTR lpCmdLine) {
  BOOL b;
  HANDLE hToken;
  HANDLE hNewToken;
  // PWSTR szProcessName = L"LowClient";
  PWSTR szIntegritySid = L"S-1-16-4096";
  PSID pIntegritySid = NULL;
  TOKEN_MANDATORY_LABEL TIL = {0};
  PROCESS_INFORMATION ProcInfo = {0};
  STARTUPINFO StartupInfo = {0};
  ULONG ExitCode = 0;

  b = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
  b = DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation,
                       TokenPrimary, &hNewToken);
  b = ConvertStringSidToSid(szIntegritySid, &pIntegritySid);
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
  b = CreateProcessAsUser(hNewToken, NULL, lpCmdLineT, NULL, NULL, FALSE, 0,
                          NULL, NULL, &StartupInfo, &ProcInfo);
  free(lpCmdLineT);
  return b;
}

HRESULT WINAPI CreateProcessInvokeBase(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory)
{
    HRESULT hr=S_OK;
    return hr;
}


HRESULT WINAPI CreateProcessWithNonElevated(LPCWSTR exePath, LPCWSTR cmdArgs,
                                            LPCWSTR workDirectory) {


  wchar_t userName[MAX_PATH] = {0};
  DWORD BufferSize = MAX_PATH;
  GetUserNameW(userName, &BufferSize);
  if (wcscmp(userName, L"Administrator") == 0) {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    SecureZeroMemory(&si, sizeof(si));
    SecureZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    HRESULT hr = S_OK;
    if ((hr = CreateProcessWithShellToken(exePath, cmdArgs, workDirectory, si,
                                          pi)) == S_OK) {
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);
    }
    return hr;
  }
  return TaskUACRunNonElevated(exePath, cmdArgs, workDirectory);
}
