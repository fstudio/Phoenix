#Visual Studio NMake Makefile

PROJECT=Phoenix
CXX=cl /Tp
CC=cl /Tc
LD=link
!IFDEF WIN64
AS=ml64
!ELSE
AS=ml
!END
INCLUDE=./wtl/include

all:
	$(CXX) -I$(INCLUDE) 
	cd lib &&nmake -f build.mk
	cd source&&nmake -f Phoenix.mk
	cd tools&&nmake -f build.mk
	
clean:
	cd lib &&nmake -f build.mk clean
	cd source&&nmake -f Phoenix.mk clean
	del /s /q *.obj *.pdb *.exe *.res >NUL
	
