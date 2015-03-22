////Container
#include "Precompiled.h"
#include "ContainerAPI.h"
#include "AppContainer.hpp"
#include <string>
#include <vector>

const wchar_t *ContainerHostJobObject = L"Phoenix.Container.JobObject.APIv1\0";

bool RemoveContainerInstance(unsigned dwFlags)
{
  switch(dwFlags)
  {
    case 0:
    break;
    default:
    break;
  }
  return true;
}

int ContainerInstance(std::wstring relFile, std::wstring cmdArgs) {
  if (PathFileExistsW(relFile.c_str()) != TRUE)
    return -1;
  return 0;
}

class Container {
private:
  unsigned Id;
  ///std::vector<int> idvector;
public:
  Container() {}
  bool Initialize() {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool bRet=AppContainer::AppContainerInitialize();
    return bRet;
  }
  bool Execute(std::wstring appPath,std::wstring command)
  {
	  return false;
  }
  bool Stop() {
    CoUninitialize();
    bool bRet=AppContainer::AppContainerDelete(RemoveContainerInstance);
    return true;
  }
};

/// Windows JobObject sample.
/// SetInformationJobObject
#ifdef DEBUG
int wmian(int argc,wchar_t** argv)
{
	Container container;
	HRESULT hr=S_OK;
	if(!container.Initialize())
		return -1;
	container.Stop();
	return 0;
}

#else

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  int ret=0;
  if((ret=LauncherContainerStatChecker())!=0)
    return ret;
  Container container;
  HRESULT hr=S_OK;
  if (!container.Initialize())
    return -1;
  /*HRESULT hr = CreateProcessWithNonElevated(
      L"C:/Windows/System32/WindowsPowerShell/v1.0/powershell_ise.exe", nullptr,
      nullptr);*/
  // MessageBoxW(nullptr,L"X",L"Wait",MB_OK);
  // CreateLowLevelProcess(L"cmd"); //this app only read auth.
  container.Stop();
  return hr;
}
#endif
