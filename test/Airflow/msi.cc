#include <Windows.h>
#include <Msi.h>
#include <Msiquery.h>
#include <string>

#pragma comment(lib,"Msi")
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(lib,"gdi32")

UINT WINAPI RecoverInstallerPackage(const wchar_t *szPackagePath,const wchar_t *szRecoverPath)
{
    //MsiConfigureProductExW
    //MsiInstallProduct()
	INSTALLTYPE InstallType=INSTALLTYPE_NETWORK_IMAGE;
	std::wstring td=L"TARGETDIR=";
    td+=szRecoverPath;
    MsiInstallProductW(szPackagePath,td.c_str());
    return 0;
}

UINT WINAPI RecoverInstallerPackageWithDB(const wchar_t *szPackagePath,const wchar_t *szRecoverPath)
{
    return 0;
}


int wmain(int argc,wchar_t **argv){
	if(argc>1)
	{
		RecoverInstallerPackage(argv[0],L"%TEMP%\\Expand");
	}
	return 0;
}
