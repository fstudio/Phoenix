###whois
TARGET=whois.exe
CC=cl
LINK=link
CXXFLAGS=-nologo -TP -W3  -Zc:forScope  -MT -DNODEBUG -EHsc -O2
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=ws2_32.lib  kernel32.lib
OBJECTS=whois.obj 
RCFILE=whois.res


all:$(TARGET)

$(TARGET):$(OBJECTS) $(RCFILE)
	$(LINK) $(LDFLAGS) -OUT:$@ $** $(LIBRARY)
	
{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<

$(RCFILE):whois.rc
	rc whois.rc

clean:
	-del *.exe *.obj *.res