#include <iostream>
#include "quadtree.h"

int main() {
	quadtree q(0,0,100,100,0);

	Point p1(10,10);
	Point p2(70,70);
	Point p3(10,70);
	Point p4(70,10);
	Point p5(80,10);
	Point p6(70,80);

	q.pushPoint(p1);
	q.pushPoint(p2);
	q.pushPoint(p3);
	q.pushPoint(p4); 
	q.pushPoint(p5);
	q.pushPoint(p6);
	
	q.traverseTree();
	//q.clearQuadtree();

	return 0;
}
