###Add Library 

LIBRARYS=Shlwapi.lib

LIBRARY=LibraryCache/Utility.lib PackageRuntime/PackageRuntime.dll LibraryCache/ZipProviders.lib

all:$(LIBRARY)


$(LIBRARY):
	cd Utility &&nmake -f Makefile
	cd PackageRuntime&&nmake -f Makefile
	cd ZipProviders&&nmake -f Makefile
	
clean:
	cd Utility &&nmake -f Makefile clean
	cd PackageRuntime&&nmake -f Makefile clean
	cd ZipProviders&&nmake -f Makefile clean
	-del .\LibraryCache\*.lib


