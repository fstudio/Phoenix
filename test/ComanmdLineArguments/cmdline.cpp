#include <iostream>
#include <Windows.h>
#include <wchar.h>
#include "CommandLineArgumentsEx.hpp"
#pragma comment(lib,"Shell32")


class Arguments{
private:
    std::vector<wchar_t *> argv_;
public:
    static Arguments Main()
    {
        int ac;
        LPWSTR *w_av = CommandLineToArgvW(GetCommandLineW(), &ac);
        std::vector<std::wstring> av1(ac);
        std::vector<wchar_t const *> av2(ac);
        for (int i = 0; i < ac; i++) {
			av1[i]=w_av[i];
            av2[i] = av1[i].c_str();
        }
        LocalFree(w_av);
        return Arguments(ac,&av2[0]);
    }
    Arguments(int Argc,wchar_t const * const* Argv)
    {
        this->argv_.resize(Argc+1);
        for(int i=0;i<Argc;i++)
        {
            this->argv_[i]=wcsdup(Argv[i]);
        }
        this->argv_[Argc]=0;
    }
    ~Arguments()
    {
        for(size_t i=0;i<this->argv_.size();i++){
            free(argv_[i]);
        }
    }
    int argc()const 
    {
        return static_cast<int>(this->argv_.size() - 1);
    }
    wchar_t const* const* argv()const {
        return &this->argv_[0];
    }
};

int cmdUnknownArgument(const wchar_t *args, void *) {
std::wcout << L"cmd Unknown Options " << args
              << std::endl;
  return 1;
}


int WINAPI wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
	
    bool help=false;
    std::wstring driverModel;
    std::wstring profile;
    int port;
    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(Argc,Argv);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
                     L"Cmd Print Help");
    Args.AddArgument(L"-D", argT::SPACE_ARGUMENT, &driverModel, L"Driver Model");
    Args.AddArgument(L"-P", argT::SPACE_ARGUMENT, &port, L"Server Lister Ports");
    Args.AddArgument(L"-C", argT::SPACE_ARGUMENT, &profile, L"Set Profile");
    Args.SetUnknownArgumentCallback(cmdUnknownArgument);
    int parsed=Args.Parse();
    if(help)
    {
      std::wcout<<L"Print Usage:"<<std::endl;
      return 0;
    }
    if(parsed)
    {
      std::wcout << L"Parser:" << parsed << std::endl;
      std::wcout<<L"Profile: "<<profile<<L"\nDriver Model:"<<driverModel<<L"\nPorts:"<<port<<std::endl;
    }
    return 0;
}
