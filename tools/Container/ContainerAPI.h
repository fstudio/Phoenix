#ifndef PHOENIX_CONTAINERAPI_H
#define PHOENIX_CONTAINERAPI_H
#ifndef _WINDOWS_
#include <Windows.h>
#endif

namespace Phoenix {
enum CONTAINER_PROCESS_RUNLEVEL {
  CONTAINER_STANDARD_RLEVEL = 0,
  CONTAINER_GUEST_RLEVEL = 1,
  CONTAINER_LOW_RLEVEL = 2
};
}
HRESULT WINAPI
CreateProcessWithShellToken(LPCWSTR exePath, _In_ LPCWSTR cmdArgs,
                            _In_ LPCWSTR workDirectory, _In_ STARTUPINFOW &si,
                            _Inout_ PROCESS_INFORMATION &pi);

HRESULT WINAPI CreateProcessWithNonElevated(LPCWSTR exePath, LPCWSTR cmdArgs,
                                            LPCWSTR workDirectory);

BOOL WINAPI CreateLowLevelProcess(LPCWSTR lpCmdLine);

#endif
