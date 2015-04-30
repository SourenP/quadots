#include <iostream>
#include "quadtree2.h"

int main() {
	quadtree2 q(0,0,0,100,100,0);

	Point p1(10,10);
	Point p2(40,40);
	Point p3(10,70);
	Point p4(40,70);
	Point p5(20, 70);
	Point p6(70, 70);

	q.insert(p1);
	q.insert(p2);
	//q.insert(p3);
	//q.insert(p4);
	//q.insert(p5);
	//q.insert(p6);

	vector<Point> babies = q.getNearestNeighbours(0, make_pair(50,50));
	q.retrieve(babies, p1);

	for(Point p : babies)
		 cout << p.x << " " << p.y << endl;
	
	cout << "----------" << endl;
	q.traverseTree();
	return 0;
}
