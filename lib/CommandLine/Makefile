
CC=cl
AR = lib.exe
CFLAGS=-nologo -c -TC -W3 -O2  -Zc:forScope -Zc:wchar_t 
LIBRARY=getopt.lib
OBJS=getopt.obj wgetopt.obj

all:$(LIBRARY)

$(LIBRARY):$(OBJS)
	$(AR) $(OBJS) -out:$@

{.}.c.obj::
	$(CC) $(CFLAGS) -c $<
	
clean:
	-del *.obj *.lib
	