/*********************************************************************************************************
* SeekLauncher.hpp
* Note: Phoenix Container Runtime
* Date: @2015.05
* Author: Force Charlie
* E-mail:<forcemz@outlook.com>
* Copyright (C) 2015 The ForceStudio All Rights Reserved.
**********************************************************************************************************/
#ifndef CONTAINER_V2_SEEKLAUNCHER_HPP
#define CONTAINER_V2_SEEKLAUNCHER_HPP

struct LauncherHostTarget{
    int id;
    const wchar_t *shell;
    const wchar_t *args;
};

#define LAUNCHER_HOST_CMD 1 ///cmd.exe
#define LAUNCHER_HOST_POWERSHELL 2 //powershell.exe
#define LAUNCHER_HOST_BASH 3 //bash
#define LAUNCHER_HOST_ISOC 4 ///run with Packers launcher.
#define LAUNCHER_HOST_PYTHON 5//python
#define LAUNCHER_HOST_ZSH 6///zsh
#define LAUNCHER_HOST_VBS 7 ///vbscript
#define LAUNCHER_HOST_WJS 8 ///This JavaScript or wjs run with WScript.exe
#define LAUNCHER_HOST_JAVASCRIPT 9 ///run with node.exe
////https://msdn.microsoft.com/en-us/windows/desktop/xawadt95.aspx

#endif
