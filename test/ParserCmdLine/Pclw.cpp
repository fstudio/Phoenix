#include "ParserCommandLine.hpp"

int wmain(int argc,wchar_t** argv)
{
	ParserCommandLineW cmd(argc,argv);
	cmd.SetParserStyle(Phoenix::PCL_POSIX_NORMAL_STYLE);
	cmd.ParserBegin();
	return 0;
}
