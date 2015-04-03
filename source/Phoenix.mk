#This Makefile to Create Phoenix

#Tools
CC=cl.exe
LINK=link.exe
LIB=lib.exe
RC=rc.exe

#TOOLS PARAM
CXXFLAGS=-Tp -C -MT
LDFLAGS= -

LIBRARY=Shell32.lib Comctl32.lib Gdi32.lib d2d1.lib dwrite.lib windowcodecs.lib \
msimg32.lib usp10.lib Uxtheme.lib kernel32.lib Advapi32.lib Ole32.lib Userenv.lib Rpcrt4.lib

APPNAME=Phoenix.exe

