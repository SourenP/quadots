#include <iostream>
#include "quadtree.h"

int main() {
	quadtree q(0,0,100,100,0);
	Point p1(10,10);
	Point p2(20,20);
	q.pushPoint(p1);
	q.pushPoint(p2);
	return 0;
}
