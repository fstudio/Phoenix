#ftp tools


TARGET=ftp.exe

CC=cl
LINK=link

CFLAGS=-nologo -TC -W3  -Zc:forScope  -MT -DNODEBUG  -O2 -D_CRT_SECURE_NO_WARNINGS
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=kernel32.lib ws2_32.lib IPHlpApi.Lib

COBJS=cmds.obj cmdtab.obj domacro.obj fake.obj ftp.obj main.obj ruserpass.obj

RCFILE=ftp.res

all:$(TARGET)

$(TARGET):$(COBJS) $(RCFILE)
	$(LINK) $(LDFLAGS) -OUT:$@ $** $(LIBRARY)
	
{.}.c.obj::
	$(CC) $(CFLAGS) -c $<

$(RCFILE):ftp.rc
	rc ftp.rc
	
clean:
	-del *.obj *.res *.exe
