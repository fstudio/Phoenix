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

#pragma comment(lib,"Userenv")

//FireAPI.dll
wchar_t AppContainer::appContainerName[64] = { 0 };
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

///ReadMe this Function must run once.
bool AppContainer::AppContainerInitialize()
{
    wcscpy_s(appContainerName,L"Phoenix.Container.AppContainer.Profile.v1");
    wchar_t appContainerDisplayName[]=L"Phoenix.Container.AppContainer.Profile.v1\0";
    wchar_t appContainerDesc[2048]=L"Phoenix Container Default AppContainer Profile ,Revision 1\0";
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
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
    PSID sidImpl;
    HRESULT hr=::CreateAppContainerProfile(appContainerName,
        appContainerDisplayName,
        appContainerDesc,
        (capabilities.empty() ? NULL : &capabilities.front()), capabilities.size(), &sidImpl);
    if(hr!=S_OK)
        return false;
    FreeSid(sidImpl);
    return true;
}

bool AppContainer::AppContainerDelete(std::function<bool(unsigned)> responseTask)
{
    HRESULT hr=  DeleteAppContainerProfile(appContainerName);
    if(hr==HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED))
    {
        if(responseTask(static_cast<unsigned>(hr)))
            hr=DeleteAppContainerProfile(appContainerName);
    }
    return hr==S_OK;
}
AppContainer::AppContainer(std::wstring app,std::wstring Args,unsigned dwFlags):m_app(app),m_Args(Args),m_dwFlags(dwFlags)
{

}

bool AppContainer::Exectue()
{
    PSID appContainerSid;
    std::vector<SID_AND_ATTRIBUTES> capabilities;
    std::vector<SHARED_SID> capabilitiesSidList;
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
    HRESULT hr=DeriveAppContainerSidFromAppContainerName(appContainerName,&appContainerSid);
    if(S_OK!=hr)
        return false;
    STARTUPINFOEX siex = { sizeof(STARTUPINFOEX )};
    wchar_t *psArgs=nullptr;
    psArgs=_wcsdup(m_Args.c_str());
    SecureZeroMemory(&siex.StartupInfo, sizeof(STARTUPINFOW));
    PROCESS_INFORMATION pi;
    siex.StartupInfo.cb = sizeof(STARTUPINFOEXW);
    SIZE_T cbAttributeListSize = 0;
    BOOL bReturn = InitializeProcThreadAttributeList(
        NULL, 3, 0, &cbAttributeListSize);
    siex.lpAttributeList = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeap(), 0, cbAttributeListSize);
    bReturn = InitializeProcThreadAttributeList(siex.lpAttributeList, 3, 0, &cbAttributeListSize);
    SECURITY_CAPABILITIES sc;
    sc.AppContainerSid = appContainerSid;
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
    BOOL bRet=CreateProcessW(m_app.c_str(), psArgs,
        nullptr, nullptr,
        FALSE,
        EXTENDED_STARTUPINFO_PRESENT,
        NULL, NULL,
        reinterpret_cast<LPSTARTUPINFOW>(&siex), &pi);
    ::CloseHandle(pi.hThread);
    ::CloseHandle(pi.hProcess);
Cleanup:
    DeleteProcThreadAttributeList(siex.lpAttributeList);
    free(psArgs);
    return true;
}

