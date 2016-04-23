/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: File Stream
*   Date: 2015.04.05
*   Author: Force.Charlie
*   E-mail: <forcemz@outlook.com>
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#include <Runtime/FStream.h>
#include <string>
#include "fstream.h"

__declspec(dllexport) bool Resolve(std::wstring &str)
{
	if(str.empty())
		return false;
	auto l=str.size();
	for(auto &c:str){
		////
		if(c==':')
			c=0;
	}
	return true;
}
