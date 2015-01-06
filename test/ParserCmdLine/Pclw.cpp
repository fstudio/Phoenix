#include "ParserCommandLine.h"

int wmain(int argc,wchar_t** argv)
{
	ParserCommandLineW cmd(argc,argv);
	cmd.SetParserStyle(Phoenix::PCL_POSIX_NORMAL_STYLE);
	cmd.ParserStart();
	return 0;
}