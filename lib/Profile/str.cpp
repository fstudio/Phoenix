#include <iostream>
#include <string>

int main()
{
	std::string s="Name=This is Name";
	size_t pos;
	if((pos=s.find_first_of('='))!=std::string::npos)
	{
		std::cout<<"Pos "<<pos<<std::endl;
		std::cout<<"Key: "<<s.substr(0,pos)<<std::endl;
		std::cout<<"Value: "<<s.substr(pos+1,s.size()-pos-1)<<std::endl;
	}
	return 0;
}
