CC  = g++
CXX = g++

INCLUDES = -I../src
LDLIBS  = -L../src/ -lquadots $(shell sdl2-config --libs)

CFLAGS   = -g -Wall -std=c++0x $(INCLUDES) $(shell sdl2-config --cflags)
CXXFLAGS = -g -Wall -std=c++0x $(INCLUDES)

boids:
collisions:

.PHONY: clean
clean:
	rm -f *.o *~ a.out core boids collisions