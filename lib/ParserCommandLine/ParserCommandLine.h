////


//T->char T->wchar_t
template<class T>
class ParserCommandLine{
public:
    ParserCommandLine(int Argc,T **Argv):dwError(0)
     {
        //
     }
 private:
    int dwError;
}

extern ParserCommandLine<wchar_t> _wParserCmdLine;