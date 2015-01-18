#NMAKE Makefile.
TARGET=PackageRuntime.dll
CC=cl
LD=link
RC=rc
INCDIR=../../include
LIBRARYPATH=../../lib
CFLAGS=/TC -I$(INCDIR) -DDLLEXPORT
CXXFLAGS=/TP -I$(INCDIR) -EHsc -DDLLEXPORT
LDFLAGS=-dll
LIBRARY=ole32.lib kernel32.lib gdi32.lib  user32.lib ole32.lib
COBJS=GC.obj Http.obj jsonsl.obj manualgc.obj UUID.obj Zip.obj PackageRuntime.obj
CXXOBJS=JSONResolve.obj RAIIBIND.obj ZipArchive.obj XmlLite.obj HttpClient.obj
RESOURCES=PackageRuntime.res

all:$(TARGET)

$(TARGET):$(COBJS) $(CXXOBJS) $(RESOURCES)
	$(LD) $(LDFLAGS) $(COBJS) $(CXXOBJS) $(LIBRARY) $(RESOURCES) -out:$@ 
	
$(RESOURCES):PackageRuntime.rc
	$(RC) PackageRuntime.rc
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<
	
clean:
	-del *.obj *.dll *.res *.lib *.exp

