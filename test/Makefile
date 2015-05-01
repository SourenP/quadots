CC  = g++
CXX = g++

INCLUDES = -I../src
LDLIBS  = -L../src/ -lquadots $(shell sdl-config --libs) -lSDL2

CFLAGS   = -g -Wall -std=c++0x $(INCLUDES) $(shell sdl-config --cflags)
CXXFLAGS = -g -Wall -std=c++0x $(INCLUDES)

boids:

.PHONY: clean
clean:
	rm -f *.o *~ a.out core boids

.PHONY: all
all: clean default