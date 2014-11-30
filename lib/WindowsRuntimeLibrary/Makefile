###Makeifle for WindowsRuntimeLibrary
CC=cl
CXXFLAGS=-TP -c
MDMERGE=mdmerge
MIDL=midl

!IF [cl -c -nologo WRTCheck.cpp >NUL:]
CXXFLAGS=$(CXXFLAGS) -DDISABLE_D2D
!MESSAGE WindowsRuntimeLibrary is not available
!ENDIF

TARGETWINMD=Phoenix.Windows.Runtime.winmd

all:
	$(CC) $(CXXFLAGS) Phoenix.Windows.Runtime.cpp
	
clean:
	-del *.obj *.lib
	
