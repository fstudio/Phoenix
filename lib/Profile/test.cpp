#include <iostream>
#include <Profile/InitializeAttribute.hpp>

int main()
{
    InitializeAttribute ia(L"F:\\Development\\Phoenix\\lib\\Profile\\my.ini");
    if(ia.IsParseOK())
    {
        std::wcout<<ia.iniStructure.Print()<<std::endl;
    }
    return 0;
}
