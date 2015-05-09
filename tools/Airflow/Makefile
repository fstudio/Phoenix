
CC=cl
CXXFLAGS=-nologo -DEBUG -DUNICODE -D_UNICODE -TP  -W4 -EHsc -Zc:forScope -Zc:wchar_t
LINK=link
RC=rc
LDFLAGS=/NOLOGO -OPT:REF

LIBRARY=Shlwapi.lib kernel32.lib user32.lib  Advapi32.lib Ole32.lib Shell32.lib  Comctl32.lib  Msi.lib Lz32.lib Setupapi.lib
OBJECTS=Airflow.obj  AirflowUIUtility.obj AirflowZend.obj Expand.obj AirflowUI.obj Msi.obj 
AIRFLOW=Airflow.exe
RESOURCE=Airflow.res


all:$(AIRFLOW)

$(AIRFLOW):$(OBJECTS) $(RESOURCE)
	$(LINK) $(LDFLAGS)  -OUT:$@ $** $(LIBRARY)

{.}.cc.obj::
	$(CC) $(CXXFLAGS) -c $<	
	
$(RESOURCE):Airflow.rc
	$(RC) /d USE_NMAKE $**
	
clean:
	-del *.obj *.exe *.res
