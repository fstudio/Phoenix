#NMAKE Makefile.
TARGET=PackageRuntime.dll
CC=cl
LD=link
RC=rc
INCDIR=../../include
LIBRARYPATH=../../lib
CFLAGS=/TC -I$(INCDIR)
CXXFLAGS=/TP -I$(INCDIR)
LDFLAGS=-dll
LIBRARY=ole32.lib ZipCompress.lib kernel32.lib gdi32.lib
COBJS=GC.obj Http.obj jsonsl.obj manualgc.obj UUID.obj XmlLite.obj Zip.obj
CXXOBJS=JSONResolve.obj RAIIBIND.obj ZipArchive.obj


all:$(TARGET)

$(TARGET):$(COBJS) $(CXXOBJS) 
	$(LD) $(LDFLAGS) $(COBJS) $(CXXOBJS) -out:$@ 
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<
	
clean:
	-del *.obj *.dll

