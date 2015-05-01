CC  = g++
CXX = g++

INCLUDES =
LDLIBS  =  

CFLAGS   = -g -Wall $(INCLUDES) -std=c++0x 
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++0x

default: Dot.o Point.o
	ar rc libquadots.a Dot.o Point.o
	ranlib libquadots.a

Point.o: Point.h
Dot.o: Point.h Dot.h


.PHONY: clean
clean:
	rm -f *.o *~ a.out core libquadots.a

.PHONY: all
all: clean default