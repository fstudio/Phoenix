#Makefile
TARGET=Container.exe
DBGTARGET=ContainerD.exe
LIBS=Shlwapi.lib kernel32.lib user32.lib Taskschd.lib comsupp.lib credui.lib Advapi32.lib Ole32.lib Shell32.lib Userenv.lib Rpcrt4.lib Comctl32.lib
CC=cl
LD=link
RC=rc
AR=lib
CFLAGS=-nologo  -DUNICODE -D_UNICODE -TC -W3
CXXFLAGS=-nologo  -DUNICODE -D_UNICODE -TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t
CXXDEBUG=-Od -MTd -DDEBUG
CXXNDEBUG=-O1 -Oi -MT -DNDEBUG
LIBCOPY=../../lib/LibraryCache/libcontainer.lib
HEADERCOPY=../../include/Container/ContainerLPCClient.hpp

LDFLAGS=/NOLOGO -OPT:REF
OBJS=Container.obj ProcessLauncher.obj  Containerlogger.obj logger.obj \
ContainerJobManager.obj CommandLineArgumentsEx.obj AppContainer.obj ContainerStatus.obj ContainerServiceHub.obj Precompiled.obj
RPCGENFILE=ContainerService_c.c ContainerService_s.c ContainerService.h
###This libcontainer.lib
LIBCONTAINEROBJ=ContainerService_c.obj ContainerLPCClient.obj
LIBCONTAINER=libcontainer.lib

!IFDEF DEBUG
CXXFLAGS=$(CXXFLAGS) $(CXXDEBUG)
CCFLAGS=$(CCFLAGS) $(CXXDEBUG)
!ELSE
CXXFLAGS=$(CXXFLAGS) $(CXXNDEBUG)
CCFLAGS=$(CCFLAGS) $(CXXNDEBUG)
!ENDIF


all:$(TARGET) $(LIBCOPY) $(HEADERCOPY)

$(LIBCOPY):$(LIBCONTAINER)
	copy libcontainer.lib  ..\..\lib\LibraryCache /Y

$(HEADERCOPY):ContainerLPCClient.hpp
	copy ContainerLPCClient.hpp ..\..\include\Container /Y

$(TARGET):Container.res ContainerService_s.obj ContainerService.obj $(OBJS)
	$(LD) $(LDFLAGS)  -OUT:$@ $** $(LIBS)

Container.res:
	$(RC) Container.rc

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<

{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

$(LIBCONTAINER):$(LIBCONTAINEROBJ)
	$(AR) $(LIBCONTAINEROBJ) -out:$@

$(LIBCONTAINEROBJ):ContainerLPCClient.cc $(RPCGENFILE)
	$(CC) $(CXXFLAGS) -c ContainerLPCClient.cc
	$(CC) $(CFLAGS) -c ContainerService_c.c

#Auto Gen RPC File
$(RPCGENFILE):
	midl ContainerService.idl

clean:
	-del *.obj *.res *.exe *.lib $(RPCGENFILE)

