#include <iostream>
#include <string>


bool Analyzer(const char *str,size_t size)
{
	if(str==nullptr||size<=0)
		return false;
	auto i=0;
	const char* Ptr;
	if(str[0]=='#'||str[0]==';')
	{
		if(size>=2){
			Ptr=&str[1];
			std::cout<<"Comments: "<<Ptr<<std::endl;
			return true;
			}
			return true;
	}else if(str[0]=='['&&str[1]!=']'){
		Ptr=&str[1];
		std::cout<<"Ptr: "<<Ptr<<std::endl;
		while(i<size-1)
		{
			if(Ptr[i++]==']'){
				std::string sn=std::string(Ptr,i-1);
				std::cout<<"Section:"<<sn<<std::endl;
				std::cout<<"Ptr: "<<Ptr<<std::endl;
				return true;
			}
            //
		}
		return false;
		}else{
			while(i<size)
			{
				if(str[i++]=='=')
                {
                    std::string key=std::string(str,i-1);
					std::cout<<"Key: "<<key<<std::endl;
                    if(i<size-2);
                    {
                        Ptr=&str[i];
						std::cout<<"Value:"<<Ptr<<std::endl;
                        return true;
                    }
                    return false;
                }
            }
        }
	return true;
}


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
	Analyzer("#Comments Linker\0",strlen("#Comments Linker\0"));
	Analyzer("[IniResolveSection]",strlen("[IniResolveSection]"));
	Analyzer("Zero=0",strlen("Zero=0"));
	return 0;
}
