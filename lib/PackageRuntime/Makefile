#NMAKE Makefile.
TARGET=PackageRuntime.dll
CC=cl
LD=link
CFLAGS=/TC
CXXFLAGS=/TP
LDFLAGS=-dll
LIBRARY=ole32.lib

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(LD) $(LDFLAGS) -out:$@ 
	
clean:
	-del *.obj *.dll

