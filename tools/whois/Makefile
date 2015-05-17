###whois
TARGET=whois.exe
CC=cl
LINK=link
CFLAGS=-nologo -TC -W3  -Zc:forScope  -MT -DNODEBUG 
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=ws2_32.lib  kernel32.lib
OBJECTS=whois.obj 
RCFILE=whois.res


all:$(TARGET)

$(TARGET):$(OBJECTS) $(RCFILE)
	$(LINK) $(LDFLAGS) -OUT:$@ $** $(LIBRARY)
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

$(RCFILE):whois.rc
	rc whois.rc

clean:
	-del *.exe *.obj *.res