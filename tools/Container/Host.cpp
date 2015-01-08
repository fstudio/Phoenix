////Container
#include "Precompiled.h"
#include "ContainerAPI.h"

const wchar_t *ContainerHostJobObject = L"Phoenix.Container.JobObject.APIv1\0";

int UACLimit() { return 0; }

int ContainerInstance(std::wstring relFile, std::wstring cmdArgs) {
  if (PathFileExistsW(relFile.c_str()) != TRUE)
    return -1;
  return 0;
}

////
int ContainerInit() { return 0; }

/// Windows JobObject sample.
/// SetInformationJobObject

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  ////Main

  return 0;
}
