####Makefile for AutoCompletion



STATICLIB=AutoCompletion.lib
DYAMLIB=Phoenix.AutoCompletion.dll
CC=cl
LIB=lib
LD=link
CXXFLAGS=  -nologo -c  -TP  -DUNICODE -D_UNICODE -EHsc  -W3  -Zc:forScope -Zc:wchar_t -O2 -MT
OBJECTS=PhoenixAutoCompletion.obj
LIBS=libclang.imp
LIBDIR= ../lib
RESOURCES =PhoenixAutoCompletion.res

all: $(STATICLIB) $(DYAMLIB)

$(STATICLIB):$(OBJECTS)
	$(LIB) $(OBJECTS) $@
	
$(DYAMLIB):$(OBJECTS) $(RESOURCES)
	$(LD) $(OBJECTS) /DLL $@

$(RESOURCES):PhoenixAutoCompletion.rc
	$(RC) PhoenixAutoCompletion.rc
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<	

	
clean:
	-del *.obj *.lib *.dll
