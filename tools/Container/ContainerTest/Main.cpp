
#include "ContainerLPCClient.hpp"

int wmain()
{
	ContainerRpcManager mgr;
	if(mgr.getStatus())
	{
		mgr.Runner(L"C:/Windows/notepad.exe",L"sss",nullptr);
	}
	return 0;
}
