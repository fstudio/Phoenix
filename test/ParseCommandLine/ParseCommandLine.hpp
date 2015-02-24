#ifndef PARSECOMMANDLINE_HPP
#define PARSECOMMANDLINE_HPP
#include <string>
#include <map>

template <typename CharT=char>
class ParseCommandLine{
public:
    typedef std::basic_string<CharT> StringRef;
private:
    StringRef selfcmd;
    std::map<StringRef,StringRef> oM;
    std::map<StringRef,StringRef> *current;
public:
    ParseCommandLine()
    {
        ///
    }
    bool Parse(int Argc,const CharT **Argv)
    {
        if(Argc<1||Argv==nullptr)
            return false;
        this->selfcmd=Argv[0];//Push argv[0] to pragma self command.
        decltype(Argc) index=1;
        bool OpSTA=false;
        while(index <Argc)
        {
            if(Argv[i][0]=='-')
            {
                OpSTA=true;
            }
        }
        return true;
    }
};

#endif
