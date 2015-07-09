#Makefile this default use NMAKE format

CC=cl
AR = lib.exe
CXXFLAGS=-nologo -c -TP -W3 -O2  -Zc:forScope -Zc:wchar_t
LIBRARY=getopt.lib
OBJS=GetOptIncA.obj GetOptIncW.obj

all:$(LIBRARY)

$(LIBRARY):$(OBJS)
	$(AR) $(OBJS) -out:$@

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<

clean:
	-del *.obj *.lib
