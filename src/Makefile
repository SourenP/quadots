CC  = g++
CXX = g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES) -std=c++0x
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++0x

LDFLAGS = -g
LDLIBS  = -L../include -lSDL2

point_test = ptest
dot_test = dtest
objects = dtest.o ptest.o Point.o Dot.o Quadtree.o Simulation.o Renderer.o Control.o State.o

point_test: $(point_test)
$(point_test): ptest.o Point.o Dot.o Quadtree.o Simulation.o Renderer.o Control.o State.o

dot_test: $(dot_test)
$(dot_test): dtest.o Point.o Dot.o Quadtree.o Simulation.o Renderer.o Control.o State.o

$(objects): Point.h Dot.h 

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(point_test) $(dot_test)

.PHONY: all
all: clean default