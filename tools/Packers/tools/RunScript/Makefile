#Makefile of VBScript JavaScript

CC=cl
LINK=link

CXXFLAGS=-Tp -O2

TARGETAPP=RunScript.exe
LIBRARY=kernel32.lib
OBJS=JavaScriptRuntimeHost.obj VBScriptRuntimeHost.obj RunScript.obj


all:$(TARGETAPP)

$(TARGETAPP):$(OBJS)
	$(LINK) 
	
	
clean:
	-del *.obj *.exe
