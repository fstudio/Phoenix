/****************************************************************************************************************
* Phoenix Package Runtime Library
* Author:Force
* E-mail: forcemz@outlook.com
* Copyright 2015 ForceStudio All Rights Reserved.
*****************************************************************************************************************/
#ifndef RUNTIME_DEFINDS_H
#define RUNTIME_DEFINDS_H
#ifdef _WIN32
#   ifdef DLLEXPORT
#       define PKGEXTERN __declspec(dllexport)
#   elif defined(DLLIMPORT)
#       define PKGEXTERN __declspec(dllimport)
#   else
#       define PKGEXTERN
#   endif
#else
#   define PKGEXTERN extern
#endif

#ifdef __cplusplus
# define PKG_BEGIN_DECL extern "C" {
# define PKG_END_DECL   }
#else
 /** Start declarations in C mode */
# define PKG_BEGIN_DECL /* empty */
 /** End declarations in C mode */
# define PKG_END_DECL   /* empty */
#endif

#endif
