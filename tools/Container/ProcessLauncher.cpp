/*********************************************************************************************************
* ProcessLauncher.cpp
* Note: Phoenix Container Process Launcher
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "Precompiled.h"
#include <string>
#include <taskschd.h>
#include <comdef.h>
#include <Sddl.h>
#include <string.h>
#include "ContainerAPI.h"
#include "AppContainer.hpp"
#include "ContainerJobManager.hpp"

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

template <class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease) {
  if (*ppInterfaceToRelease != nullptr) {
    (*ppInterfaceToRelease)->Release();

    (*ppInterfaceToRelease) = nullptr;
  }
}

#define DO(action)                                                             \
  if (FAILED( action )) {                                                        \
    ASSERT( FALSE );                                                             \
    goto ClenUp;                                                               \
  }

HRESULT WINAPI ProcessLauncherNonElevatedWithTaskSchd(LPCWSTR pszPath, LPCWSTR pszParameters,
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

  LPCWSTR pszTaskName = L"Phoenix.Container-ProcessLauncherNonElevatedWithTaskSchd-Task-APIv1";

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

HRESULT WINAPI ProcessLauncherExplorerLevel(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory)
{
  STARTUPINFOW si;
  PROCESS_INFORMATION pi;
  SecureZeroMemory(&si, sizeof(si));
  SecureZeroMemory(&pi, sizeof(pi));
  si.cb = sizeof(si);
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
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  retval = true;

cleanup:
  // Clean up resources
  CloseHandle(hShellProcessToken);
  CloseHandle(hPrimaryToken);
  CloseHandle(hShellProcess);
  return hr;
}


HRESULT WINAPI ProcessLauncherMIC(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory)
{
  BOOL bRet;
  HANDLE hToken;
  HANDLE hNewToken;
  PWSTR szIntegritySid = L"S-1-16-4096";
  PSID pIntegritySid = NULL;
  TOKEN_MANDATORY_LABEL TIL = {0};
  PROCESS_INFORMATION pi = {0};
  STARTUPINFOW StartupInfo = {0};
  StartupInfo.cb=sizeof(STARTUPINFOW);
  ULONG ExitCode = 0;

  bRet = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
  if(!bRet)
    return 1;
  bRet = DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation,
                       TokenPrimary, &hNewToken);
  bRet = ConvertStringSidToSidW(szIntegritySid, &pIntegritySid);
  TIL.Label.Attributes = SE_GROUP_INTEGRITY;
  TIL.Label.Sid = pIntegritySid;
  CloseHandle(hToken);
  // Set process integrity levels
  bRet = SetTokenInformation(hNewToken, TokenIntegrityLevel, &TIL,
                          sizeof(TOKEN_MANDATORY_LABEL) +
                              GetLengthSid(pIntegritySid));

  // Set process UI privilege level
  /*b = SetTokenInformation(hNewToken, TokenIntegrityLevel,
  &TIL, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(pIntegritySid)); */
  wchar_t *lpCmdLine = _wcsdup(cmdArgs);
  // To create a new low-integrity processes
  bRet = CreateProcessAsUserW(hNewToken, exePath, lpCmdLine, NULL, NULL, FALSE, 0,
                          NULL, workDirectory, &StartupInfo, &pi);
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  CloseHandle(hToken);
  CloseHandle(hNewToken);
  LocalFree(pIntegritySid);
  free(lpCmdLine);
  return bRet?S_OK:S_FALSE;
}

HRESULT WINAPI ProcessLauncherWithAppContainer(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory)
{
  DWORD m_pid;
  return LauncherWithAppContainerEx(exePath,cmdArgs,workDirectory,m_pid);
}


unsigned WINAPI ProcessLauncherMICEx(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory)
{
  BOOL bRet;
  HANDLE hToken;
  HANDLE hNewToken;
  PWSTR szIntegritySid = L"S-1-16-4096";
  PSID pIntegritySid = NULL;
  TOKEN_MANDATORY_LABEL TIL = {0};
  PROCESS_INFORMATION pi = {0};
  STARTUPINFOW StartupInfo = {0};
  StartupInfo.cb=sizeof(STARTUPINFOW);
  ULONG ExitCode = 0;
  unsigned taskId=0;
  bRet = OpenProcessToken(GetCurrentProcess(), MAXIMUM_ALLOWED, &hToken);
  if(!bRet)
    return 1;
  bRet = DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityImpersonation,
                       TokenPrimary, &hNewToken);
  bRet = ConvertStringSidToSidW(szIntegritySid, &pIntegritySid);
  TIL.Label.Attributes = SE_GROUP_INTEGRITY;
  TIL.Label.Sid = pIntegritySid;
  CloseHandle(hToken);
  // Set process integrity levels
  bRet = SetTokenInformation(hNewToken, TokenIntegrityLevel, &TIL,
                          sizeof(TOKEN_MANDATORY_LABEL) +
                              GetLengthSid(pIntegritySid));

  // Set process UI privilege level
  /*b = SetTokenInformation(hNewToken, TokenIntegrityLevel,
  &TIL, sizeof(TOKEN_MANDATORY_LABEL) + GetLengthSid(pIntegritySid)); */
  wchar_t *lpCmdLine = _wcsdup(cmdArgs);
  // To create a new low-integrity processes
  bRet = CreateProcessAsUserW(hNewToken, exePath, lpCmdLine, NULL, NULL, FALSE, 0,
                          NULL, workDirectory, &StartupInfo, &pi);
  if(bRet){
    taskId=GetProcessId(pi.hProcess);
  }
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);
  CloseHandle(hToken);
  CloseHandle(hNewToken);
  LocalFree(pIntegritySid);
  free(lpCmdLine);
  return taskId;
}

HRESULT WINAPI ProcessLauncher(LPCWSTR exePath,LPCWSTR cmdArgs,LPCWSTR workDirectory,unsigned level)
{
    if(exePath==nullptr&&cmdArgs==nullptr)
        return S_FALSE;
    HRESULT hr=S_OK;
    BOOL bAdmin=IsUserAnAdmin();
    switch(level){
        case Phoenix::CONTAINER_INVOKER_RLEVEL:
        break;
        case Phoenix::CONTAINER_MANDATORY_INTEGRITY_CONTROL_RLEVEL:
        return ProcessLauncherMIC(exePath,cmdArgs,workDirectory);
        case Phoenix::CONTAINER_UAC_MEDIUM_RLEVEL:
        {
          if(bAdmin){
            if(_waccess(exePath,04)!=0)
              return -1;
            return ProcessLauncherNonElevatedWithTaskSchd(exePath,cmdArgs,workDirectory);
          }
        }
        case Phoenix::CONTAINER_APPCONTAINER_RLEVEL:
        return ProcessLauncherWithAppContainer(exePath,cmdArgs,workDirectory);
        case Phoenix::CONTAINER_RUNINJOB:
        return ContainerJobManager::StartRestrictedProcess(exePath,cmdArgs,workDirectory);
        default:
        break;
    }
    return ProcessLauncherWithAppContainer(exePath,cmdArgs,workDirectory);
}


HRESULT WINAPI ProcessLauncherWithNonElevated(LPCWSTR exePath, LPCWSTR cmdArgs,
                                            LPCWSTR workDirectory) {
  wchar_t userName[MAX_PATH] = {0};
  DWORD BufferSize = MAX_PATH;
  GetUserNameW(userName, &BufferSize);
  if (wcscmp(userName, L"Administrator") == 0) {
    return ProcessLauncherExplorerLevel(exePath,cmdArgs,workDirectory);
  }
  return ProcessLauncherNonElevatedWithTaskSchd(exePath, cmdArgs, workDirectory);
}
