#include <iostream>
#include "quadtree.h"

int main() {
	quadtree q(0,0,100,100,0);
	Point p1(10,10);
	Point p2(70,70);
	q.pushPoint(p1);
	q.pushPoint(p2);
	q.clearQuadtree();
	return 0;
}
