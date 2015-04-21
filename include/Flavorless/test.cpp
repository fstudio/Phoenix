#include "FlavorlessLoader.hpp"


int main()
{
    FlavorlessLoader<wchar_t> sz;
    sz.Detect(L"./FlavorlessLoader.hpp");
    return 0;
}
