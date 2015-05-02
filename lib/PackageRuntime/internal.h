/*********************************************************************************************************
*   Phoenix Package Runtime
*   Note: Internal defined
*   Date: 2015.01.13
*   Copyright (C) 2015 ForceStudio.All Rrights Reserved.
**********************************************************************************************************/
#ifndef PHOENIX_PACKAGE_RUNTIME_INTERNAL_H
#define PHOENIX_PACKAGE_RUNTIME_INTERNAL_H
#include <stdio.h>
#include <stdarg.h>
inline void Out(const char* fmt,...)
{
	va_list args;
	int cnt;
	va_start(args,fmt);
	cnt=vprintf(fmt,args);
	va_end(args);
}

#ifdef __cplusplus
namespace detail {
  inline void consume() { }
  template <typename T0, typename... T>
  void consume(const T0 & t0, const T &... t) { (void)t0; consume(t...); }
}

#define noop(...) \
 (void)([&](){detail::consume(__VA_ARGS__);})
#else
#define noop(...) do { } while(0)
#endif

#ifdef DEBUG
#ifdef __cplusplus
extern "C"{
#endif
void TRACE(FILE *fp,const char* format,...);
#ifdef __cplusplus
}
#endif
#eles
#define TRACE noop;
#endif
