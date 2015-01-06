#include <stdio.h>
#include <stdlib.h>
#include "ParserCommandLine.h"

using namespace Phoenix;

bool ParserCommandLine::ParserPowerShellStyleBegin()
{
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

///////////////////////////////////////////////////////////////////
bool ParserCommandLineW::ParserPowerShellStyleBegin()
{
    this->pStatus=true;
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
