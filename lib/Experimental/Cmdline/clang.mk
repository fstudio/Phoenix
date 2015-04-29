#Makefile This Mingw64 and Clang
CC=clang
AR = ar
CFLAGS= -std=c11 -c -O2 
LIBRARY=libgetopt.a
OBJECTS=getopt.o wgetopt.o

all:$(LIBRARY)

$(LIBRARY):$(OBJECTS)
	$(AR) rcs $(LIBRARY) $(OBJECTS)

	
$(OBJECTS): %.o: %.c
	$(CC) $(CFLAGS)  $< -o $@
	
clean:
	-rm *.o *.a
	