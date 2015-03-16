import core.sys.windows;
module UserEnv;
version (Windows):
pragma(lib, "Userenv.lib");
/*typedef struct PROC_THREAD_ATTRIBUTE_ENTRY
{
    DWORD_PTR   Attribute;  // PROC_THREAD_ATTRIBUTE_xxx
    SIZE_T      cbSize;
    PVOID       lpValue;
} 
alias PROC_THREAD_ATTRIBUTE_ENTRY* LPPROC_THREAD_ATTRIBUTE_ENTRY;
 
// This structure contains a list of attributes that have been added using UpdateProcThreadAttribute
typedef struct PROC_THREAD_ATTRIBUTE_LIST
{
    DWORD                          dwFlags;
    ULONG                          Size;
    ULONG                          Count;
    ULONG                          Reserved;  
    PULONG                         Unknown;
    PROC_THREAD_ATTRIBUTE_ENTRY    Entries[1];
} 
alias PROC_THREAD_ATTRIBUTE_LIST* PPROC_THREAD_ATTRIBUTE_LIST,LPPROC_THREAD_ATTRIBUTE_LIST;
*/

alias LPVOID PPROC_THREAD_ATTRIBUTE_LIST;

typedef struct STARTUPINFOEX_W {
  STARTUPINFO_W                 StartupInfo;
  PPROC_THREAD_ATTRIBUTE_LIST lpAttributeList;
} 
alias STARTUPINFOEX_W* LPSTARTUPINFOEXW;

alias PVOID PISD;
struct SID_AND_ATTRIBUTES {
  PSID  Sid;
  DWORD Attributes;
} 
alias SID_AND_ATTRIBUTES *PSID_AND_ATTRIBUTES;

enum WELL_KNOWN_SID_TYPE{ 
  WinNullSid                                   = 0,
  WinWorldSid                                  = 1,
  WinLocalSid                                  = 2,
  WinCreatorOwnerSid                           = 3,
  WinCreatorGroupSid                           = 4,
  WinCreatorOwnerServerSid                     = 5,
  WinCreatorGroupServerSid                     = 6,
  WinNtAuthoritySid                            = 7,
  WinDialupSid                                 = 8,
  WinNetworkSid                                = 9,
  WinBatchSid                                  = 10,
  WinInteractiveSid                            = 11,
  WinServiceSid                                = 12,
  WinAnonymousSid                              = 13,
  WinProxySid                                  = 14,
  WinEnterpriseControllersSid                  = 15,
  WinSelfSid                                   = 16,
  WinAuthenticatedUserSid                      = 17,
  WinRestrictedCodeSid                         = 18,
  WinTerminalServerSid                         = 19,
  WinRemoteLogonIdSid                          = 20,
  WinLogonIdsSid                               = 21,
  WinLocalSystemSid                            = 22,
  WinLocalServiceSid                           = 23,
  WinNetworkServiceSid                         = 24,
  WinBuiltinDomainSid                          = 25,
  WinBuiltinAdministratorsSid                  = 26,
  WinBuiltinUsersSid                           = 27,
  WinBuiltinGuestsSid                          = 28,
  WinBuiltinPowerUsersSid                      = 29,
  WinBuiltinAccountOperatorsSid                = 30,
  WinBuiltinSystemOperatorsSid                 = 31,
  WinBuiltinPrintOperatorsSid                  = 32,
  WinBuiltinBackupOperatorsSid                 = 33,
  WinBuiltinReplicatorSid                      = 34,
  WinBuiltinPreWindows2000CompatibleAccessSid  = 35,
  WinBuiltinRemoteDesktopUsersSid              = 36,
  WinBuiltinNetworkConfigurationOperatorsSid   = 37,
  WinAccountAdministratorSid                   = 38,
  WinAccountGuestSid                           = 39,
  WinAccountKrbtgtSid                          = 40,
  WinAccountDomainAdminsSid                    = 41,
  WinAccountDomainUsersSid                     = 42,
  WinAccountDomainGuestsSid                    = 43,
  WinAccountComputersSid                       = 44,
  WinAccountControllersSid                     = 45,
  WinAccountCertAdminsSid                      = 46,
  WinAccountSchemaAdminsSid                    = 47,
  WinAccountEnterpriseAdminsSid                = 48,
  WinAccountPolicyAdminsSid                    = 49,
  WinAccountRasAndIasServersSid                = 50,
  WinNTLMAuthenticationSid                     = 51,
  WinDigestAuthenticationSid                   = 52,
  WinSChannelAuthenticationSid                 = 53,
  WinThisOrganizationSid                       = 54,
  WinOtherOrganizationSid                      = 55,
  WinBuiltinIncomingForestTrustBuildersSid     = 56,
  WinBuiltinPerfMonitoringUsersSid             = 57,
  WinBuiltinPerfLoggingUsersSid                = 58,
  WinBuiltinAuthorizationAccessSid             = 59,
  WinBuiltinTerminalServerLicenseServersSid    = 60,
  WinBuiltinDCOMUsersSid                       = 61,
  WinBuiltinIUsersSid                          = 62,
  WinIUserSid                                  = 63,
  WinBuiltinCryptoOperatorsSid                 = 64,
  WinUntrustedLabelSid                         = 65,
  WinLowLabelSid                               = 66,
  WinMediumLabelSid                            = 67,
  WinHighLabelSid                              = 68,
  WinSystemLabelSid                            = 69,
  WinWriteRestrictedCodeSid                    = 70,
  WinCreatorOwnerRightsSid                     = 71,
  WinCacheablePrincipalsGroupSid               = 72,
  WinNonCacheablePrincipalsGroupSid            = 73,
  WinEnterpriseReadonlyControllersSid          = 74,
  WinAccountReadonlyControllersSid             = 75,
  WinBuiltinEventLogReadersGroup               = 76,
  WinNewEnterpriseReadonlyControllersSid       = 77,
  WinBuiltinCertSvcDComAccessGroup             = 78,
  WinMediumPlusLabelSid                        = 79,
  WinLocalLogonSid                             = 80,
  WinConsoleLogonSid                           = 81,
  WinThisOrganizationCertificateSid            = 82,
  WinApplicationPackageAuthoritySid            = 83,
  WinBuiltinAnyPackageSid                      = 84,
  WinCapabilityInternetClientSid               = 85,
  WinCapabilityInternetClientServerSid         = 86,
  WinCapabilityPrivateNetworkClientServerSid   = 87,
  WinCapabilityPicturesLibrarySid              = 88,
  WinCapabilityVideosLibrarySid                = 89,
  WinCapabilityMusicLibrarySid                 = 90,
  WinCapabilityDocumentsLibrarySid             = 91,
  WinCapabilitySharedUserCertificatesSid       = 92,
  WinCapabilityEnterpriseAuthenticationSid     = 93,
  WinCapabilityRemovableStorageSid             = 94
} 
/*
WELL_KNOWN_SID_TYPE
*/
enum {
EXTENDED_STARTUPINFO_PRESENT =0x00080000
}

export(Windows) @nogc{
HRESULT
CreateAppContainerProfile(
    PCWSTR pszAppContainerName,
    PCWSTR pszDisplayName,
    PCWSTR pszDescription,
    PSID_AND_ATTRIBUTES pCapabilities,
    DWORD dwCapabilityCount,
    PVOID* ppSidAppContainerSid);

HRESULT DeleteAppContainerProfile(
    PCWSTR pszAppContainerName);

}
	