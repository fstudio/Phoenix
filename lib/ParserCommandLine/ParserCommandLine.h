////
#include<string>
#include <map>
//T->char T->wchar_t
template<class T>
class ParserCommandLine{
private:
	int m_Argc;
	char **m_Argv;
    int dwError;
	std::map<std::string,std::string> OpCode;
	std::vector<std::string> OpValue;
public:
    ParserCommandLine(int Argc,char **Argv):dwError(0)
     {
        //
     }
};


class ParserCommandLineW{
private:
	int m_Argc;
	wchar_t **m_Argv;
    int dwError;
	std::map<std::wstring,std::wstring> OpCode;
	std::vector<std::wstring> OpValue;
public:
    ParserCommandLine(int Argc,wchar_t **Argv):dwError(0)
     {
        //
     }
};