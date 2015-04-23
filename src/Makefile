CC  = g++
CXX = g++

INCLUDES =

CFLAGS   = -g -Wall $(INCLUDES) -std=c++0x
CXXFLAGS = -g -Wall $(INCLUDES) -std=c++0x

LDFLAGS = -g
LDLIBS  = -L../include -lSDL2

executables = Main
objects = Main.o Simulation.o Point.o State.o

.PHONY: default
default: $(executables)

$(executables): Main.o Simulation.o Point.o State.o
$(objects): Simulation.h Point.h State.h

.PHONY: clean
clean:
	rm -f *~ a.out core $(objects) $(executables)

.PHONY: all
all: clean default