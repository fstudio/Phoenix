#ifndef PARSECOMMANDLINE_HPP
#define PARSECOMMANDLINE_HPP
#include <string>

template <typename CharT=char>
class ParseCommandLine{
public:
    typedef basic_string<CharT> StringRef;
private:
    StringRef selfcmd;
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
        return true;
    }
};

#endif
