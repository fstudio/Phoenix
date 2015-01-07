/**
* Parser CommandLine Utils.
**/
#include <stdio.h>
#include <stdlib.h>
#include "ParserCommandLine.hpp"

using namespace Phoenix;

bool ParserCommandLine::ParserPowerShellStyleBegin()
{
	for (auto i = 1; i < m_Argc; i++)
	{
		if (m_Argv[i][0] == '-')
		{
			if (i + 1 < m_Argc&&m_Argv[i + 1][0] != '-')
			{
				OpCode.insert(std::map<std::string, std::string>::value_type(m_Argv[i], m_Argv[i + 1]));
				i++;
			}
			else
			{
				OpCode.insert(std::map<std::string,std::string>::value_type(m_Argv[i],"\0"));
			}
		}
	}
    return true;
}

bool ParserCommandLine::ParserPOSIXStyleBegin()
{
    return true;
}

bool ParserCommandLine::ParserDOSStyleBegin()
{
    return true;
}

bool ParserCommandLine::ParserBegin()
{
    switch(this->style)
    {
        case PCL_POWERSHELL_STYLE:
        return this->ParserPowerShellStyleBegin();
        case PCL_POSIX_NORMAL_STYLE:
        return this->ParserPOSIXStyleBegin();
        case PCL_DOS_BASPLIT_STYLE:
        return this->ParserDOSStyleBegin();
        default:
        break;
    }
    return false;
}

bool ParserCommandLine::PushCommandTask(std::function<int(std::string)> task,std::string param)
{
    if(task==nullptr)
        return false;
	this->Task.insert(std::map<std::string, std::function<int(std::string)>>::value_type(param, task));
    return true;
}

bool ParserCommandLine::ExecuteTask()
{
    std::map<std::string,std::string>::iterator it;
	for (it = OpCode.begin(); it != OpCode.end(); ++it)
	{
		//printf(it->first.c_str());
		std::map<std::string, std::function<int(std::string)>>::iterator iter;
		for (iter = this->Task.begin(); iter != Task.end(); ++iter)
		{
			if (iter->first == it->first)
				(iter->second)(it->second);
		}
	}
    return true;
}

///////////////////////////////////////////////////////////////////
bool ParserCommandLineW::ParserPowerShellStyleBegin()
{
	for (auto i = 1; i < m_Argc; i++)
	{
		if (m_Argv[i][0] == '-')
		{
			if (i + 1 < m_Argc&&m_Argv[i + 1][0] != '-')
			{
				OpCode.insert(std::map<std::wstring, std::wstring>::value_type(m_Argv[i], m_Argv[i + 1]));
				i++;
			}
			else
			{
				OpCode.insert(std::map<std::wstring, std::wstring>::value_type(m_Argv[i], L"\0"));
			}
		}
	}
	return true;
}

bool ParserCommandLineW::ParserPOSIXStyleBegin()
{
    return true;
}

bool ParserCommandLineW::ParserDOSStyleBegin()
{
    return true;
}

bool ParserCommandLineW::ParserBegin()
{
    switch(this->style)
    {
        case PCL_POWERSHELL_STYLE:
        return this->ParserPowerShellStyleBegin();
        case PCL_POSIX_NORMAL_STYLE:
        return this->ParserPOSIXStyleBegin();
        case PCL_DOS_BASPLIT_STYLE:
        return this->ParserDOSStyleBegin();
        default:
        break;
    }
    return false;
}

bool ParserCommandLineW::PushCommandTask(std::function<int(std::wstring)> task, std::wstring param)
{
	if (task == nullptr)
		return false;
	this->Task.insert(std::map<std::wstring, std::function<int(std::wstring)>>::value_type(param, task));
	return true;
}


bool ParserCommandLineW::ExecuteTask()
{
	std::map<std::wstring, std::wstring>::iterator it;
	for (it = OpCode.begin(); it != OpCode.end(); ++it)
	{
		std::map<std::wstring, std::function<int(std::wstring)>>::iterator iter;
		for (iter = this->Task.begin(); iter != Task.end(); ++iter)
		{
			if (iter->first==it->first)
				(iter->second)(it->second);
		}
	}
	return true;
}
