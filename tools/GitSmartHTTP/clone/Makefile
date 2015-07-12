#!/usr/bin/env nmake
#Header enable with MSYS2

TARGET=git-clone-stress.exe

CC=cl
LINK=link

CMFLAGS=-nologo -O2 -MT -W3 -Zc:forScope -DUNICODE -D_UNICODE -DNODEBUG 
#CMFLAGS=-nologo  -D_DEBUG -MTd -W3 -Zc:forScope -DUNICODE -D_UNICODE  
CFLAGS=$(CMFLAGS) -TP
CXXFLAGS=$(CMFLAGS) -TP -EHsc  -Zc:wchar_t
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=kernel32.lib ws2_32.lib user32.lib  crypt32.lib Winhttp.lib Shlwapi.lib

CXXOBJS=url.obj git-clone-stress.obj GetOptInc.obj

RCFILE=git-clone-stress.res

all:$(TARGET)

$(TARGET):$(COBJS) $(CXXOBJS) $(RCFILE)
	$(LINK) $(LDFLAGS) -OUT:$@ $** $(LIBRARY)
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<

{.}.rc.res::
	$(RC)  $<

	
clean:
	-del *.obj *.res *.exe
