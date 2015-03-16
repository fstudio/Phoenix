import core.runtime;
import core.sys.windows;
import UserEnv;

bool AppContainerLauncherApp(string appPath,string cmdArgs,string workDir)
{
   WELL_KNOWN_SID_TYPE capabilitiyTypeList[] = {
   WinCapabilityInternetClientSid, WinCapabilityInternetClientServerSid, WinCapabilityPrivateNetworkClientServerSid,
   WinCapabilityPicturesLibrarySid, WinCapabilityVideosLibrarySid, WinCapabilityMusicLibrarySid,
   WinCapabilityDocumentsLibrarySid, WinCapabilitySharedUserCertificatesSid, WinCapabilityEnterpriseAuthenticationSid,
   WinCapabilityRemovableStorageSid,
   };
  return true;
}

int main(string[] args)
{

}
