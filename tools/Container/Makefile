#Makefile
TARGET=Container.exe
LIBS=Shlwapi.lib kernel32.lib user32.lib Taskschd.lib comsupp.lib credui.lib Advapi32.lib Ole32.lib
CC=cl
LD=link
RC=rc
CFLAGS=-nologo -DNODEBUG -DUNICODE -D_UNICODE -O1 -Oi -MT 
CXXFLAGS=-TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t
LDFLAGS=/NOLOGO -OPT:REF  
OBJS=Precompiled.obj UACProcess.obj Host.obj 



all:$(TARGET)

$(TARGET):Container.res $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) Container.res -OUT:$@ $(LIBS)

Container.res:
	$(RC) Container.rc

{.}.cpp.obj::
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	-del *.obj *.res *.exe

