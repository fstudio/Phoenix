#Chakrahost Makefile

TARGET=ChakraHost.exe
CC=cl
LINK=link
CXXFLAGS=-nologo -TP -W3 -Ehsc -Zc:forScope -Zc:wchar_t -DUNICODE -D_UNICODE -MT -DNODEBUG
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib \
oleaut32.lib uuid.lib odbc32.lib odbccp32.lib jsrt.lib
OBJECTS=ChakraHost.obj Profiler.obj stdafx.obj
RCFILE=ChakraHost.res


all:$(TARGET)

$(TARGET):$(OBJECTS) $(RCFILE)
	$(LINK) $(LDFLAGS) -OUT:$@ $** $(LIBRARY)
	
{.}.cpp.obj::
	$(CC) $(CXXFLASG) -c $<

$(RCFILE):ChakraHost.rc
	rc ChakraHost.rc

clean:
	-del *.exe *.obj *.res