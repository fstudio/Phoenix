#Utility Library Makefile
#
LIBRARYNAME=Utility.lib
CC=cl.exe
LIB=lib.exe
INCDIR=-I../../include
CFLAGS=-TC -c  -DUNICODE -D_UNICODE -EHsc  -W3  -Zc:forScope -Zc:wchar_t -O2 -MT $(INCDIR)
CXXFLAGS=-TP -c -EHsc -O2 -W3 -O2  -Zc:forScope -Zc:wchar_t -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -MT $(INCDIR)
COBJS=Base64.obj EncodingC.obj String.obj MD5.obj
CXXOBJS=Directory.obj DynamicLoader.obj EncodingCXX.obj FStream.obj Glob.obj RegularExpression.obj\
StringBuffer.obj SystemTools.obj

all:$(LIBRARYNAME)

$(LIBRARYNAME):$(COBJS) $(CXXOBJS)
	$(LIB) $(COBJS) $(CXXOBJS) -out:$@

{.}.c.obj::
	$(CC) $(CFLAGS) $<

{.}.cxx.obj::
	$(CC) $(CXXFLAGS) $<

clean:
	@-if exist *.obj del /s /q *.obj >nul 2>nul
	@-if exist *.lib  del /s /q *.lib >nul 2>nul
