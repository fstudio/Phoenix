#Makefile This Mingw64 and Clang
CXX=clang++
AR = ar
CXXFLAGS= -std=c++11 -c -O2 
LIBRARY=libgetopt.a
OBJECTS=GetOptIncA.o GetOptIncW.o

all:$(LIBRARY)

$(LIBRARY):$(OBJECTS)
	$(AR) rcs $(LIBRARY) $(OBJECTS)

	
$(OBJECTS): %.o: %.c
	$(CXX) $(CXXFLAGS)  $< -o $@
	
clean:
	-rm *.o *.a
	