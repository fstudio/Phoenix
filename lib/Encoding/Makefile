#NMake Makefile Encoding.lib

TARGET=Encoding.lib
CC=cl
LIB=lib
CXXFLAGS=/TP  -EHsc  -W3  -Zc:forScope -Zc:wchar_t -O2 
CFLAGS=/TC -W3  -Zc:forScope -Zc:wchar_t -O2 
CXXOBJS=StringConvertWin.obj
COBJS=ConvertUTF.obj


all:$(TARGET)

$(TARGET):$(CXXOBJS) $(COBJS)
	$(LIB) $(COBJS) $(CXXOBJS) -out:$@ 

{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

{.}.cpp.obj::
	$(CC) $(CXXFLAGS) -c $<
	
clean:
	-del *.obj *.lib
