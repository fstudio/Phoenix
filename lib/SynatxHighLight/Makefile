###Makefile

CC=cl
LD=link
RC=rc
LIB=lib

CXXFLAGS=/TP
LDFLAGS=-dll

DLLNAME=Synatx.HighLight.dll
LIBNAME=Synatx.HighLightST.lib

all:$(LIBNAME)


dll:$(DLLNAME)

$(LIBNAME):SyntaxRules.obj

$(DLLNAME):SyntaxRules.obj

clean:
	-del *.dll *.obj *.lib
	
