
CC=cl
CXXFLAGS=-nologo -DEBUG -DUNICODE -D_UNICODE -TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t
LINK=link
RC=rc
MT=mt
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=Shlwapi.lib kernel32.lib user32.lib  Advapi32.lib Ole32.lib Shell32.lib  Comctl32.lib  Msi.lib Lz32.lib Setupapi.lib
OBJECTS=Airflow.obj  AirflowUIUtility.obj AirflowZend.obj Expand.obj AirflowUI.obj Msi.obj 
AIRFLOW=Airflow.exe
RFLAGS=/d USE_MAKE
RESOURCE=Airflow.res


all:$(AIRFLOW)

$(AIRFLOW):$(OBJECTS) $(RESOURCE)
	$(LINK) $(LDFLAGS)  -OUT:$@ $** $(LIBRARY)
	$(MT) -manifest Airflow.manifest  -outputresource:$(AIRFLOW)

{.}.cc.obj::
	$(CC) $(CXXFLAGS) -c $<	
	
.rc.res:
	$(RC) $(RFLAGS)  /r $<
	
clean:
	-del *.obj *.exe *.res
