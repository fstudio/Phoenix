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
Phoenix:
	$(CXX) -I$(INCLUDE) 

clean:
	del /s /q *.obj *.pdb *.exe *.res >NUL
	
