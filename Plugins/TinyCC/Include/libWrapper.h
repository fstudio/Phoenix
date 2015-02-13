/*********************************************************************************************************
*   Phoneix libWrapper.h
*   Note: Launcher Main
*   Data: 2015.01.18
**********************************************************************************************************/
#ifndef  PHONEIX_PLUGIN_LIBWRAPPER_H
#define PHONEIX_PLUGIN_LIBWRAPPER_H

#ifdef _WIN64
#include "../X64/tcc/libtcc/libtcc.h"
#else
#include "../X86/tcc/libtcc/libtcc.h"
#endif

#define CompilerStatus TCCState
#define CompilerNew tcc_new
#define CompilerDelete tcc_delete
#define CompilerSetLibPath tcc_set_lib_path
#define CompilerSetErrorCallback tcc_set_error_func
#define CompilerSetOptions tcc_set_options
#define CompilerAddIncludePath tcc_add_include_path
#define CompilerAddSysIncludePath tcc_add_sysinclude_path
#define CompilerDefineSymbol tcc_define_symbol
#define CompilerUndefineSymbol tcc_undefine_symbol
#define CompilerAddFile tcc_add_file
#define CompilerCompileString tcc_compile_string
#define CompilerSetOutputType tcc_set_output_type


enum CompilerOutTypeFlags{
 COMPILER_OUT_MEMORY=0,
 COMPILER_OUT_EXE=1,
 COMPILER_OUT_DLL=2,
 COMPILER_OUT_LIB=3,
 COMPILER_OUT_PROCESS=4
};
#define CompilerAddLibraryPath tcc_add_library_path
#define CompilerAddSymbol tcc_add_symbol
#define CompilerOutputFile tcc_output_file
#define CompilerRun tcc_run
#define CompilerRelocate tcc_relocate
#define CompilerGetSymbol tcc_get_symbol

#define COMPILER_RELOCATE_AUTO (void*)1

#endif