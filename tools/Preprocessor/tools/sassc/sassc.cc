/*********************************************************************************************************
* sass.cc
* Note: Phoenix Preprocessor Sass compiler
* Date: @2015.04
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <sass2scss.h>
#include <sass_context.h>
#define STRIP_FLAG_HELP 1
#include <gflags/gflags.h>

using GFLAGS_NAMESPACE::SetUsageMessage;
using GFLAGS_NAMESPACE::ParseCommandLineFlags;
using GFLAGS_NAMESPACE::int32;
using GFLAGS_NAMESPACE::FlagRegisterer;
using GFLAGS_NAMESPACE::StringFromEnv;
using GFLAGS_NAMESPACE::RegisterFlagValidator;
using GFLAGS_NAMESPACE::CommandLineFlagInfo;
using GFLAGS_NAMESPACE::GetAllFlags;


DEFINE_bool(service,false,"Run Sassc With RPC Service");

int main(int argc,char **argv)
{
    SetUsageMessage("Phoenix Sassc Preprocessor Engine Usage:");
    ParseCommandLineFlags(&argc,&argv,true);
    return 0;
}

