###NMake This Core GC Build
LIBRARY=CoreGC.lib
CC=cl
AR=lib
CXXFLAGS=-c -D_DEBUG -DWIN32 -DUNICODE -D_UNICODE -D_CONSOLE -D_LIB -I. -ZI -nologo -W3 -WX- -sdl -Od -Gm -EHsc -RTC1 -GS -Zc:wchar_t -Zc:forScope -TP

OBJECTS=gccommon.obj gceewks.obj gcenv.obj gcscan.obj gcwks.obj handletable.obj \
handletablecache.obj handletablescan.obj objecthandle.obj gcenv.obj common.obj

all:$(LIBRARY)

$(LIBRARY):$(OBJECTS)
	$(AR) $(OBJECTS) -out:$@
	
{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<
	
clean:
	-del *.obj *.lib *.idb *.pdb
