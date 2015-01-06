#include "ParserCommandLine.h"

int main(int argc,char** argv)
{
	ParserCommandLine cmd(argc,argv);
	cmd.SetParserStyle(Phoenix::PCL_POSIX_NORMAL_STYLE);
	cmd.ParserStart();
	return 0;
}