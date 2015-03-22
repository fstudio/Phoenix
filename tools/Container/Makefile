#Makefile
TARGET=Container.exe
DBGTARGET=ContainerD.exe
LIBS=Shlwapi.lib kernel32.lib user32.lib Taskschd.lib comsupp.lib credui.lib Advapi32.lib Ole32.lib Shell32.lib Userenv.lib
CC=cl
LD=link
RC=rc
CFLAGS=-nologo  -DUNICODE -D_UNICODE -TC -W3 
CXXFLAGS=-nologo  -DUNICODE -D_UNICODE -TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t
CXXDEBUG=-Od -MTd -DDEBUG
CXXNDEBUG=-O1 -Oi -MT -DNDEBUG 


LDFLAGS=/NOLOGO -OPT:REF  
OBJS=Container.obj ProcessLauncher.obj  AppContainer.obj ContainerStatus.obj ContainerService.obj Precompiled.obj  
RPCGENFILE=ContainerService_c.c ContainerService_s.c ContainerService.h


!IFDEF DEBUG
CXXFLAGS=$(CXXFLAGS) $(CXXDEBUG)
CCFLAGS=$(CCFLAGS) $(CXXDEBUG)
!ELSE
CXXFLAGS=$(CXXFLAGS) $(CXXNDEBUG)
CCFLAGS=$(CCFLAGS) $(CXXNDEBUG)
!ENDIF


all:$(TARGET)

$(TARGET):Container.res $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) Container.res -OUT:$@ $(LIBS)

Container.res:
	$(RC) Container.rc

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<
	
##RPC MDI Auto
RPCGEN:
	midl ContainerService.idl

clean:
	-del *.obj *.res *.exe $(RPCGENFILE)

