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
COBJS=GC.obj  UUID.obj Zip.obj PackageRuntime.obj CppRest.obj  getCommandLineOpt.obj URIPorts.obj
CXXOBJS=JSONResolveEx.obj JSONResolve.obj RAIIBIND.obj ZipArchive.obj  XmlResolve.obj FileStream.obj \
Base64Encoder.obj RuntimeDebug.obj md5.obj UriParser.obj  StringBuffer.obj fstream.obj
RESOURCES=PackageRuntime.res
TINYXMLOBJ=tinyxml2.obj
TINYXMLFILE=tinyxml2.cpp tinyxml2.h

all:$(TARGET)

$(TARGET):$(COBJS) $(CXXOBJS) $(TINYXMLOBJ) $(RESOURCES)
	$(LD) $(LDFLAGS) $(COBJS) $(CXXOBJS) $(TINYXMLOBJ) $(LIBRARY) $(RESOURCES) -out:$@ 

	
.rc.res:
	$(RC) $(RFLAGS) /r $<
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<

{.}.cc.obj::
	$(CC) $(CXXFLAGS) -c $<

$(TINYXMLOBJ):$(TINYXMLFILE)
	$(CC) $(CXXFLAGS) -c tinyxml2.cpp
	
$(TINYXMLFILE):
	@copy ..\..\deps\tinyxml2\tinyxml2.cpp tinyxml2.cpp /Y
	@copy ..\..\deps\tinyxml2\tinyxml2.h tinyxml2.h /Y

clean:
	@-if exist *.obj del /s /q *.obj >nul 2>nul
	@-if exist *.lib  del /s /q *.lib >nul 2>nul
	@-if exist *.res del /s /q *.res >nul 2>nul
	@-if exist *.dll  del /s /q *.dll >nul 2>nul
	@-if exist *.exp del /s /q *.exp >nul 2>nul
	@-if exist tinyxml2.cpp del /s /q tinyxml2.cpp >nul 2>nul
	@-if exist tinyxml2.h del /s /q tinyxml2.h >nul 2>nul
