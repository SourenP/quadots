#include <iostream>
#include "quadtree2.h"

int main() {
	quadtree2 q(0,0,100,100,0);
	Point p1(10,10);
	Point p2(70,70);
	Point p3(10,70);
	Point p4(70,10);

	q.insert(p1);
	//q.insert(p2);
	//q.insert(p3);
	//q.insert(p4); 
	//q.pushPoint(p5);
	//q.pushPoint(p6);
	
	q.traverseTree();

	//std::cout<<"Done traversal. Now looking for neighbours.....\n";


	//q.getNearestNeighbours(root);
	//std::vector<Point> temp = q.getNearestNeighbours(p2);
	
	//std::cout<<"size= "<<temp.size()<<"\n";
	//for (int i = 0; i < temp.size(); i++)
	//	std::cout<<temp[i].x<<","<<temp[i].y<<"\n";
	
	//q.clearQuadtree();

	return 0;
}
