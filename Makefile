all:
	g++ -g -Wall -std=c++0x -c quadtree2.cpp
	g++ -g -Wall -std=c++0x -c main.cpp
	g++ -g -Wall -std=c++0x quadtree2.o main.o -o test 

clean:
	rm -f quadtree2.o main.o test
