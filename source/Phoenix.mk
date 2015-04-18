#This Makefile to Create Phoenix

#Tools
CC=cl
LD=link
AR=lib
RC=rc
#Target
APPNAME=Phoenix.exe

#TOOLS PARAM
CXXFLAGS=-nologo  -DUNICODE -D_UNICODE -TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t -MT
LDFLAGS=-NOLOGO -OPT:REF
INCDIR=-I../include -I../wtl/Include
LIBPATHDIR=../lib/LibraryCache
#Library
LIBRARYS=Shlwapi.lib kernel32.lib user32.lib Taskschd.lib comsupp.lib credui.lib Advapi32.lib Uxtheme.lib  Gdi32.lib\
Ole32.lib Shell32.lib Userenv.lib Rpcrt4.lib Comctl32.lib d2d1.lib dwrite.lib Windowscodecs.lib msimg32.lib usp10.lib

###Build Library

##Object
OBJECTS=UIWindow.obj CommandLineArgumentsEx.obj Direct2DResourceManager.obj EditorRender.obj \
FontAwesome.obj IFileWindowUI.obj ManagerThread.obj MessageWindow.obj Mutex.obj PhoenixDPIUtils.obj \
PhoenixThread.obj SearchWindowSelf.obj StandarndIO.obj TaskProcess.obj Phoenix.obj
#Resource
RESOURCEFILE=Phoenix.res

all:$(APPNAME)

$(APPNAME):Phoenix.res $(OBJECTS)
	$(LD) $(LDFLAGS) -OUT:$@ $**  $(LIBRARYS) -LIBPATH:$(LIBPATHDIR)

Phoenix.res:
	$(RC) Phoenix.rc

{.}.cpp.obj::
	$(CC) $(INCDIR) $(CXXFLAGS) -c $<

clean:
	-del *.obj *.res *.exe
