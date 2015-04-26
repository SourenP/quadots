#include <iostream>
#include "quadtree.h"

int main() {
	quadtree q(0,0,100,100,0);
	Point p(10,10);
	q.pushPoint(p);
	return 0;
}
