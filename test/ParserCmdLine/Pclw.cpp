#include "ParserCommandLine.hpp"
#include <iostream>
#ifndef _WIN32
#endif
#include <Windows.h>
#pragma comment(lib,"kernel32")
#pragma comment(lib,"user32")
#pragma comment(lib,"gdi32")

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

int TaskTest(std::wstring ab)
{
	MessageBoxW(nullptr,ab.c_str(),L"TaskTesting");
	return 0;
}


int wmain(int argc,wchar_t** argv)
{
	ParserCommandLineW cmd(argc,argv);
	cmd.SetParserStyle(Phoenix::PCL_POWERSHELL_STYLE);
	cmd.PushCommandTask(TaskTest,L"-help");
	cmd.ParserBegin();
	cmd.ExecuteTask();
	return 0;
}
