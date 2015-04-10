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


int wmain(int argc,wchar_t **argv)
{
    Arguments arguments=Arguments::Main();
    int Argc=arguments.argc();
    wchar_t const  *const* Argv=arguments.argv();
	
    bool help=false;
    std::wstring driverModel;
    std::wstring profile;
    std::vector<std::wstring> vfile;
    int port=0;
    typedef Force::CommandLineArguments argT;
    Force::CommandLineArguments Args;
    Args.Initialize(argc,argv);
    Args.StoreUnusedArguments(true);
    Args.AddArgument(L"--help", argT::NO_ARGUMENT, &help,
                     L"Cmd Print Help");
    Args.AddArgument(L"-D", argT::SPACE_ARGUMENT, &driverModel, L"Driver Model");
    Args.AddArgument(L"-P", argT::SPACE_ARGUMENT, &port, L"Server Lister Ports");
    Args.AddArgument(L"-C", argT::SPACE_ARGUMENT, &profile, L"Set Profile");
    Args.AddArgument(L"-F", argT::MULTI_ARGUMENT, &vfile, L"Load File");
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
	  for(auto &u:vfile)
	  {
		  std::wcout<<u<<std::endl;
	  }
	  wchar_t** newArgv = 0;
	  int newArgc = 0;
	  Args.GetRemainingArguments(&newArgc, &newArgv);
	  for(int i=0;i<newArgc;i++)
	  {
		  std::wcout<<L"No Used File: "<<newArgv[i]<<std::endl;
	  }
	  Args.DeleteRemainingArguments(newArgc, &newArgv);
    }
    return 0;
}
