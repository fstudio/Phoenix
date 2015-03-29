/*********************************************************************************************************
* AppContainer.cpp
* Note: Phoenix Container AppContainer
* E-mail:<forcemz@outlook.com>
* Data: @2015.03
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include "AppContainer.hpp"
#include <vector>
#include <memory>
#include <type_traits>
#include <Windows.h>
#include <sddl.h>
#include <Userenv.h>
#include "ContainerAPI.h"


#pragma comment(lib,"Userenv")


static const wchar_t appContainerProfileName[]=L"Phoenix.Container.AppContainer.Profile.APIv1\0";


class CharPtr{
private:
    wchar_t *Ptr;
public:
    CharPtr(const wchar_t *constPtr):Ptr(nullptr)
    {
        if(constPtr)
        {
            Ptr=_wcsdup(constPtr);
        }
    }
    ~CharPtr()
    {
        if(Ptr)
            free(Ptr);
    }
    wchar_t *get()
    {
        return this->Ptr;
    }
};

void AppContainerLocalFree(PSID sid) {
  if (sid != NULL) {
    ::LocalFree(sid);
  }
}

typedef std::shared_ptr<std::remove_pointer<PSID>::type> SHARED_SID;
SHARED_SID ToSharedSID(PSID sid) {
  return SHARED_SID(sid, &AppContainerLocalFree);
}

void AppContainerFreeSid(PSID sid) {
  if (sid != NULL) {
    ::FreeSid(sid);
  }
}

SHARED_SID ToSharedSID2(PSID sid) {
  return SHARED_SID(sid, &AppContainerFreeSid);
}


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
    ///range-based for
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

bool DeleteAppContainerProfileRestricted(std::function<bool(unsigned)> rmTask)
{
    HRESULT hr=  DeleteAppContainerProfile(appContainerProfileName);
    if(hr==HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED))
    {
        if(rmTask(static_cast<unsigned>(hr)))
            hr=DeleteAppContainerProfile(appContainerProfileName);
    }
    return hr==S_OK;
}

HRESULT AppContainerProfileInitialize()
{
    wchar_t appContainerDisplayName[]=L"Phoenix.Container.AppContainer.Profile.APIv1\0";
    wchar_t appContainerDesc[2048]=L"Phoenix Container Default AppContainer Profile ,API Revision 1\0";
    DeleteAppContainerProfile(appContainerProfileName);
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
    if(!MakeWellKnownSIDAttributes(capabilities,capabilitiesSidList)){
        return S_FALSE;
    }
    PSID sidImpl;
    HRESULT hr=::CreateAppContainerProfile(appContainerProfileName,
        appContainerDisplayName,
        appContainerDesc,
        (capabilities.empty() ? NULL : &capabilities.front()), capabilities.size(), &sidImpl);
    if(sidImpl)
    {
        FreeSid(sidImpl);
    }
    return hr;
}


HRESULT LauncherWithAppContainerEx(LPCWSTR pszApp,LPCWSTR cmdArgs,LPCWSTR workDir,DWORD &pid)
{
    PSID appContainerSid;
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
    if(!MakeWellKnownSIDAttributes(capabilities,capabilitiesSidList)){
        return 1;
    }
    HRESULT hr=DeriveAppContainerSidFromAppContainerName(appContainerProfileName,&appContainerSid);
    if(S_OK!=hr){
        return 2;
    }
    STARTUPINFOEX siex = { sizeof(STARTUPINFOEX )};
    CharPtr charPtr(cmdArgs);
    DWORD taskId=0;
    SecureZeroMemory(&siex.StartupInfo, sizeof(STARTUPINFOW));
    PROCESS_INFORMATION pi;
    siex.StartupInfo.cb = sizeof(STARTUPINFOEXW);
    SIZE_T cbAttributeListSize = 0;
    InitializeProcThreadAttributeList(NULL, 3, 0, &cbAttributeListSize);
    siex.lpAttributeList = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, cbAttributeListSize);
    BOOL bReturn=TRUE;
    if((bReturn = InitializeProcThreadAttributeList(siex.lpAttributeList, 3, 0, &cbAttributeListSize))==FALSE)
    {
        hr=4;
        goto Cleanup;
    }
    SECURITY_CAPABILITIES sc;
    sc.AppContainerSid = appContainerSid;
    sc.Capabilities = (capabilities.empty() ? NULL : &capabilities.front());
    sc.CapabilityCount = capabilities.size();
    sc.Reserved = 0;
    if((bReturn=UpdateProcThreadAttribute(siex.lpAttributeList, 0,
        PROC_THREAD_ATTRIBUTE_SECURITY_CAPABILITIES,
        &sc,
        sizeof(sc) ,
        NULL, NULL))==FALSE)
    {
        hr=5;
        goto Cleanup;
    }
    if((bReturn=CreateProcessW(pszApp, charPtr.get(),
        nullptr, nullptr,
        FALSE,
        EXTENDED_STARTUPINFO_PRESENT,
        NULL, workDir,
        reinterpret_cast<LPSTARTUPINFOW>(&siex), &pi))==FALSE)
    {
        pid=0;
        hr=6;
        goto Cleanup;
    }
    pid=GetProcessId(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
Cleanup:
    DeleteProcThreadAttributeList(siex.lpAttributeList);
    FreeSid(appContainerSid);
    return hr;
}

unsigned LauncherWithAppContainer(LPCWSTR pszApp,LPCWSTR cmdArgs,LPCWSTR workDir)
{
    DWORD m_pid=0;
    HRESULT hr=0;
    if((hr=LauncherWithAppContainerEx(pszApp,cmdArgs,workDir,m_pid))==S_OK)
    {
        return m_pid;
    }
    return 0;
}

