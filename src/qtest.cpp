#include <iostream>
#include "Point.h"
#include "Quadtree.cpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
	Quadtree<Point::Point_p> *q = new Quadtree<Point::Point_p>(0,0,100,100);

	Point::Point_p p1(new Point(10, 10,-1));
	Point::Point_p p2(new Point(40, 40,-1));
	Point::Point_p p3(new Point(10, 60,-1));
	Point::Point_p p4(new Point(20, 60,-1));
	Point::Point_p p5(new Point(60, 60,-1));	

	q->insert(p1);
	q->insert(p2);
	q->insert(p3);
	q->insert(p4);
	q->insert(p5);

	vector<Point::Point_p> n = q->getNearestNeighbours(p2, 300);
	cout << n.size() << endl;

	delete q;
}