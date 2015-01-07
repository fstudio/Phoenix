////
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <assert.h>

namespace Phoenix{
    enum PARSER_CMDLINE_STYLE
    {
    PCL_POSIX_NORMAL_STYLE=1,/// -key=value.
    PCL_POWERSHELL_STYLE=2,/// -File D:/OPT/helloworld.cpp -Reset -Force
    PCL_DOS_BASPLIT_STYLE=3 //// /? /help.
    };
}

class ParserCommandLine{
private:
    int m_Argc;
    char **m_Argv;
    int dwError;
    bool pStatus;
    std::map<std::string,std::string> OpCode;
    std::map<std::string,std::function<int(std::string)>> Task;
    std::vector<std::string> OpValue;
    unsigned style;
public:
    void SetParserStyle(unsigned i)
    {
		this->style=i;
    }
    ParserCommandLine(int Argc,char **Argv):dwError(0),pStatus(false),m_Argc(Argc)
    {
        assert(Argv);
        m_Argv=Argv;
    }
    bool ParserBegin();
    bool PushCommandTask(std::function<int(std::string)> task,std::string param);
    bool ExecuteTask();
private:
    bool ParserPowerShellStyleBegin();
    bool ParserPOSIXStyleBegin();
    bool ParserDOSStyleBegin();
};


class ParserCommandLineW{
private:
    int m_Argc;
    wchar_t **m_Argv;
    int dwError;
    bool pStatus;
    std::map<std::wstring,std::wstring> OpCode;
    std::map<std::wstring,std::function<int(std::wstring)>> Task;
    std::vector<std::wstring> OpValue;
    unsigned style;
public:
    void SetParserStyle(unsigned i)
    {
        this->style=i;
    }
    ParserCommandLineW(int Argc,wchar_t **Argv):dwError(0),pStatus(false),m_Argc(Argc)
    {
        assert(Argv);
        m_Argv=Argv;
    }
    bool ParserBegin();
	bool PushCommandTask(std::function<int(std::wstring)> task, std::wstring param);
private:
	bool ExecuteTask();
    bool ParserPowerShellStyleBegin();
    bool ParserPOSIXStyleBegin();
    bool ParserDOSStyleBegin();
};

