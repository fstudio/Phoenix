
#include "ContainerLPCClient.hpp"
#include <iostream>

void Call(ContainerRpcManager &cm)
{
	///
}

int wmain(int argc,wchar_t **argv)
{
	ContainerRpcManager mgr;
	if(mgr.IsInitialize())
	{
		std::cout<<"Return Code: "<<mgr.Runner(L"C:/Windows/notepad.exe",nullptr,nullptr)<<std::endl;
	}
	Sleep(3000);
	if(argc>=2)
	{
		if(wcscmp(argv[1],L"exit")==0)
		{
			mgr.Destory();
		}
	}
	return 0;
}
