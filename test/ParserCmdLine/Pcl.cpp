#include "ParserCommandLine.hpp"
#include <iostream>

int TaskTest(std::string ab)
{
	std::cout<<ab<<std::endl;
	return 0;
}


int main(int argc,char** argv)
{
	ParserCommandLine cmd(argc,argv);
	cmd.SetParserStyle(Phoenix::PCL_POSIX_NORMAL_STYLE);
	cmd.PushCommandTask(TaskTest,"-help");
	cmd.ParserBegin();
	cmd.ExecuteTask();
	return 0;
}
