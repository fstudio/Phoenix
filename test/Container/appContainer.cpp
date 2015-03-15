#include <vector>
#include <memory>
#include <type_traits>
#include <Windows.h>
#include <sddl.h>
#include <Userenv.h>
#include <iostream>

#pragma comment(lib,"Userenv")
#pragma comment(lib,"Shlwapi")
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(lib,"Advapi32")
#pragma comment(lib,"Ole32")
#pragma comment(lib,"Shell32")

typedef std::shared_ptr<std::remove_pointer<PSID>::type> SHARED_SID;

bool SetCapability(const WELL_KNOWN_SID_TYPE type, std::vector<SID_AND_ATTRIBUTES> &list, std::vector<SHARED_SID> &sidList) {
  SHARED_SID capabilitySid(new unsigned char[SECURITY_MAX_SID_SIZE]);
  DWORD sidListSize = SECURITY_MAX_SID_SIZE;
  if (::CreateWellKnownSid(type, NULL, capabilitySid.get(), &sidListSize) == FALSE) {
    return false;
  }
  if (::IsWellKnownSid(capabilitySid.get(), type) == FALSE) {
    return false;
  }
  SID_AND_ATTRIBUTES attr;
  attr.Sid = capabilitySid.get();
  attr.Attributes = SE_GROUP_ENABLED;
  list.push_back(attr);
  sidList.push_back(capabilitySid);
  return true;
}

static bool MakeWellKnownSIDAttributes(std::vector<SID_AND_ATTRIBUTES> &capabilities,std::vector<SHARED_SID> &capabilitiesSidList)
{

    const WELL_KNOWN_SID_TYPE capabilitiyTypeList[] = {
        WinCapabilityInternetClientSid, WinCapabilityInternetClientServerSid, WinCapabilityPrivateNetworkClientServerSid,
        WinCapabilityPicturesLibrarySid, WinCapabilityVideosLibrarySid, WinCapabilityMusicLibrarySid,
        WinCapabilityDocumentsLibrarySid, WinCapabilitySharedUserCertificatesSid, WinCapabilityEnterpriseAuthenticationSid,
        WinCapabilityRemovableStorageSid,
    };
    for(auto type:capabilitiyTypeList) {
        if (!SetCapability(type, capabilities, capabilitiesSidList)) {
            return false;
        }
    }
    return true;
}


HRESULT AppContainerLauncherProcess(LPCWSTR app,LPCWSTR cmdArgs,LPCWSTR workDir)
{
    wchar_t appContainerName[]=L"Phoenix.Container.AppContainer.Profile.v1.test";
    wchar_t appContainerDisplayName[]=L"Phoenix.Container.AppContainer.Profile.v1.test\0";
    wchar_t appContainerDesc[]=L"Phoenix Container Default AppContainer Profile  Test,Revision 1\0";
	DeleteAppContainerProfile(appContainerName);///Remove this AppContainerProfile
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
    if(!MakeWellKnownSIDAttributes(capabilities,capabilitiesSidList))
        return S_FALSE;
    PSID sidImpl;
    HRESULT hr=::CreateAppContainerProfile(appContainerName,
        appContainerDisplayName,
        appContainerDesc,
        (capabilities.empty() ? NULL : &capabilities.front()), capabilities.size(), &sidImpl);
    if(hr!=S_OK){
		std::cout<<"CreateAppContainerProfile Failed"<<std::endl;
		return hr;
	}
	wchar_t *psArgs=nullptr;
    psArgs=_wcsdup(cmdArgs);
    PROCESS_INFORMATION pi;
	STARTUPINFOEX siex = { sizeof(STARTUPINFOEX) };
    siex.StartupInfo.cb = sizeof(STARTUPINFOEXW);
    SIZE_T cbAttributeListSize = 0;
    BOOL bReturn = InitializeProcThreadAttributeList(
        NULL, 3, 0, &cbAttributeListSize);
    siex.lpAttributeList = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, cbAttributeListSize);
    bReturn = InitializeProcThreadAttributeList(siex.lpAttributeList, 3, 0, &cbAttributeListSize);
    SECURITY_CAPABILITIES sc;
    sc.AppContainerSid = sidImpl;
    sc.Capabilities = (capabilities.empty() ? NULL : &capabilities.front());
    sc.CapabilityCount = capabilities.size();
    sc.Reserved = 0;
    if(UpdateProcThreadAttribute(siex.lpAttributeList, 0,
        PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES,
        &sc,
        sizeof(sc) ,
        NULL, NULL)==FALSE)
    {
        goto Cleanup;
    }
    BOOL bRet=CreateProcessW(app, psArgs, nullptr, nullptr,
		FALSE, EXTENDED_STARTUPINFO_PRESENT, NULL, workDir, reinterpret_cast<LPSTARTUPINFOW>(&siex), &pi);
    ::CloseHandle(pi.hThread);
    ::CloseHandle(pi.hProcess);
Cleanup:
    DeleteProcThreadAttributeList(siex.lpAttributeList);
	DeleteAppContainerProfile(appContainerName);
    free(psArgs);
    FreeSid(sidImpl);
    return hr;
}

int wmain(int argc,wchar_t *argv[])
{
	if(argc>=2)
	{
		std::wcout<<L"Start AppContainer App: "<<argv[1]<<L"\t Return Code[HRESULT]: "<<AppContainerLauncherProcess(nullptr,argv[1],nullptr)<<std::endl;
	}
	return 0;
}
