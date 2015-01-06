#MAKEFILE

CC=cl
LD=link
RC=rc
CXXFLAGS= -O2 -c
LDFLAGS= -NOLOGO -dll -NOENTRY

all:Phoenix.Resources.dll

Phoenix.Resources.dll:PhoenixResources.res dllmain.obj
	$(LD) dllmain.obj PhoenixResources.res $(LDFLAGS) -out:$@ 
	
#dllmain.obj add ,not parser machine
dllmain.obj:
	$(CC) $(CXXFLAGS) dllmain.cpp

PhoenixResources.res:
	$(RC) PhoenixResources.rc
	
clean:
	-del *.obj *.res *.dll
