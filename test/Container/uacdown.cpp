#include <Windows.h>
#include <stdio.h>
#include <shlobj.h>
#include <Shlwapi.h>
#include <Objbase.h>
#include <string>
#include <taskschd.h>
#include <comdef.h>
#include <Sddl.h>
#include <string.h>
#include <wchar.h>


#pragma comment(lib,"Shlwapi")
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(lib,"Taskschd")
#pragma comment(lib,"comsupp")
#pragma comment(lib,"credui")
#pragma comment(lib,"Advapi32")
#pragma comment(lib,"Ole32")
#pragma comment(lib,"Shell32")

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

int wmain(int argc,wchar_t *argv[])
{
	if(argc>=2)
	{
		CoInitialize(NULL);
		if(_waccess(argv[1],04)==0&&IsUserAnAdmin())
		{
			wprintf(L"TaskUACRunNonElevated Process: %d\n",TaskUACRunNonElevated(argv[1],nullptr,nullptr));
	    }else{
			wprintf(L"Not Found This App,Or Not a Administrator User: %s\n",argv[1]);
		}
		CoUninitialize();
	}
	return 0;
}


