#ZipCompress Module
#NMAKE Module

PROJECT= ZipCompress.lib
CC = cl.exe
AR = lib.exe
LD = link.exe
LIBCACHE=..\LibraryCache
CXXFLAGS =  -nologo -c  -TP  -DUNICODE -D_UNICODE -EHsc  -W3  -Zc:forScope -Zc:wchar_t -O2 -MT
WFLAGS  = -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE
CFLAGS =  -nologo -c -TC -W3 -O2  -Zc:forScope -Zc:wchar_t -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -MT
ARFLAGS =  -nologo
INCDIR= -I../../include
OBJS = adler32.obj compress.obj crc32.obj deflate.obj gzclose.obj gzlib.obj gzread.obj gzwrite.obj\
 infback.obj inflate.obj inftrees.obj inffast.obj trees.obj uncompr.obj zutil.obj  ioapi.obj iowin32.obj mztools.obj  unzip.obj zip.obj


 
 
all: $(PROJECT) $(LIBCACHE)\$(PROJECT)

$(PROJECT): ZipCompress.obj $(OBJS)
	$(AR) ZipCompress.obj $(OBJS) -out:$@

ZipCompress.obj:
	$(CC) $(CXXFLAGS) $(INCDIR) ZipCompress.cpp

{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

$(LIBCACHE)\$(PROJECT):$(PROJECT)
	copy $(PROJECT) $@
	
clean:
	-del /s /q *.obj *.lib >nul 2>nul

	
	