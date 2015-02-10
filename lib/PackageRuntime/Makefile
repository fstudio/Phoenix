#NMAKE Makefile.
TARGET=PackageRuntime.dll
CC=cl
LD=link
RC=rc
INCDIR=../../include
LIBRARYPATH=../../lib/LibraryCache
CFLAGS=/TC -I$(INCDIR) -DDLLEXPORT 
CXXFLAGS=/TP -I$(INCDIR) -EHsc -DDLLEXPORT
LDFLAGS=-dll
LIBRARY=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib \
ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libcmt.lib winhttp.lib
COBJS=GC.obj  UUID.obj Zip.obj PackageRuntime.obj CppRest.obj
CXXOBJS=JSONResolveEx.obj JSONResolve.obj RAIIBIND.obj ZipArchive.obj  XmlResolve.obj  tinyxml2.obj Base64Encoder.obj RuntimeDebug.obj md5.obj
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

{.}.cc.obj::
	$(CC) $(CXXFLAGS) -c $<

clean:
	-del *.obj *.dll *.res *.lib *.exp

