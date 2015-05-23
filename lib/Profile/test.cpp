#include <iostream>
#include <Windows.h>
#include <Profile/InitializeAttribute.hpp>

int main()
{
    InitializeAttribute ia(L"F:\\Development\\Phoenix\\lib\\Profile\\my.ini");
    if(ia.IsParseOK())
    {
		std::wcout.imbue(std::locale("chs"));
        std::wcout<<ia.iniStructure.Print()<<std::endl;
		//MessageBoxW(nullptr,ia.iniStructure.Print().c_str(),L"Chinese",MB_OK);
    }
    return 0;
}
