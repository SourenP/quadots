#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <stack>
#include "quadtree.h"
#include "Point.h"

std::vector<Point> neighboursList; 

quadtree::quadtree(double x, double y, double width, double height, int level) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->level = level;
	this->split = false;

	this->nodes[0] = NULL;
	this->nodes[1] = NULL;
	this->nodes[2] = NULL;
	this->nodes[3] = NULL;
}


quadtree::~quadtree() {
	if (this->nodes[0] != NULL) delete this->nodes[0];
	if (this->nodes[1] != NULL) delete this->nodes[1];
	if (this->nodes[2] != NULL) delete this->nodes[2];
	if (this->nodes[3] != NULL) delete this->nodes[3];
}

void quadtree::pushPoint(Point p) {
	int result;
	if (points.size() < MAX_POINTS) {
		points.push_back(p);
		return;
	}

	if (nodes[0] != NULL) {
		int index = getIndex(p);
		if (index != -1) {
			this->nodes[index]->pushPoint(p);
			return;
		}
	}

	if (nodes[0] == NULL) {
		result = splitIntoQuads();
		int index = getIndex(p);
		if (index != -1) {
			this->nodes[index]->pushPoint(p);
			return;
		}
	}
}
	
int quadtree::getIndex(Point p) {
	int index = -1;
	bool topquad, bottomquad;
	topquad = bottomquad = false;

	double verMidpoint = this->x + 0.5*this->width;
	double horMidpoint = this->y + 0.5*this->height;

	if (p.y < horMidpoint)
		topquad = true;
	else if (p.y > horMidpoint)
		bottomquad = true;

	if (topquad) {
		if (p.x < verMidpoint)
			index = 0;
		else if (p.x > verMidpoint)
			index = 1;
	}
	else if (bottomquad) {
		if (p.x > verMidpoint)
			index = 2;
		else if (p.x < verMidpoint)
			index = 3;
	}

	return index; 
}

int quadtree::splitIntoQuads() {
	int newWidth = width/2;
	int newHeight = height/2;
	int newLevel = level + 1;
	if (newLevel < MAX_LEVELS) {
		nodes[0] = new quadtree(x, y, newWidth, newHeight, newLevel);
		nodes[1] = new quadtree(x + newWidth, y, newWidth, newHeight, newLevel);
		nodes[2] = new quadtree(x + newWidth, y + newHeight, newWidth, newHeight, newLevel);
		nodes[3] = new quadtree(x, y + newHeight, newWidth, newHeight, newLevel);
		split = true;
		return 1;
	}
	return 0;		//can't split
}

void quadtree::clearQuadtree() {
	if (split == false) {
		points.erase(points.end() - 1);		//start erasing from the end
		return;
	}

	for (int i = 0; i < MAX_NODES; i++) {
		if (split == true) {
			nodes[i]->clearQuadtree();
			//this->split = false;
		}
	}
	split = false;
}
/*
int quadtree::traverseTree(quadtree* q, Point p) {
	std::cout<<"Inside traverse tree ugh.. on level "<<this->level<<"\n";
	int found = -1;
	if (q->nodes[0] == NULL) {		//calling node has no children
		std::cout<<"hullooooo\n";

		std::cout<<this->nodes[0]->points.size()<<"\n";
		std::cout<<this->points[0].x<<","<<this->points[0].y<<"\n";

		if (q->x == p.x && q->y == p.y) {
			std::cout<<"hullo\n";
			return q->level; 
		}
		else
			return -1;	//point not found
	}
	else if (nodes[0] != NULL) {	//calling nodes has children
		found = traverseTree(nodes[0], p);
		if (found != -1)
			return found;
		else
			found = traverseTree(nodes[1], p);
		if (found != -1)
			return found;
		else
			found = traverseTree(nodes[2], p);
		if (found == -1)
			return found;
		else
			found = traverseTree(nodes[3], p);
	}
	return found;
}
*/
quadtree quadtree::traverseTree(quadtree* q, int level) {
	quadtree temp(-1,-1,-1,-1,-1);

	if (q->level == level)
		return *this;
		
	if (split == true) {
		temp = traverseTree(q->nodes[0], level);
		if (temp.x == -1)
			temp = traverseTree(q->nodes[1], level);
		if (temp.x == -1)
			temp = traverseTree(q->nodes[2], level);
		if (temp.x == -1)
			temp = traverseTree(q->nodes[3], level);
	}
	
	return temp;
}
/*
std::vector<Point> quadtree::getNearestNeighbours(Point p) {
	//int level = traverseTree(p);
	std::cout<<"Level found: "<<level<<"\n";
	std::vector<Point> nearest_points;

	if (level != -1)
		nearest_points = getPointsAtLevel(level - 1);
	else
		std::cout<<"Error!";		//error handling? 

	std::map<double, int> neighbours;

	for (int i = 0; i < nearest_points.size(); i++)	{ //change to iterator	
		neighbours[getDistance(nearest_points[i], p)] = i;
	}

	std::vector<Point> fin_neighbours;	//final list of neighbours;
	
	std::map<double, int>::iterator it;
	int i = 0;
	for (it = neighbours.begin(); it != neighbours.end(); it++) { 
		if (i < 4) {			//get 4 closest points
			fin_neighbours.push_back(nearest_points[it->second]);
			i++;
		}
		else
			break;
	}
	
	return fin_neighbours; 
	return nearest_points;
}

*/

std::vector<Point> quadtree::getPointsAtLevel(int level) {
	std::vector<Point> foundPoints;
	quadtree foundQuad = traverseTree(this, level);
	
	if (foundQuad.split == true) {
		foundPoints.push_back(Point(foundQuad.nodes[0]->x, foundQuad.nodes[0]->y));
		foundPoints.push_back(Point(foundQuad.nodes[1]->x, foundQuad.nodes[1]->y));
		foundPoints.push_back(Point(foundQuad.nodes[2]->x, foundQuad.nodes[2]->y));
		foundPoints.push_back(Point(foundQuad.nodes[3]->x, foundQuad.nodes[3]->y));
	}
	else if (foundQuad.split == false) {
		foundPoints.push_back(Point(foundQuad.x, foundQuad.y));
	}

	return foundPoints;
}

double quadtree::getDistance(Point p1) {
	Point p2 = this->points[0];
	return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));	
}

/* Use this function for testing */
void quadtree::traverseTree() {
	if (this->nodes[0] == NULL) {
		for (int i = 0; i < this->points.size(); i++)
			std::cout<<"At level "<<this->level<<", we have: "<<points[i].x<<","<<points[i].y<<"\n";
		return;
	}
	for (int i = 0; i < this->points.size(); i++)
		std::cout<<"At level "<<this->level<<", we have: "<<points[i].x<<","<<points[i].y<<"\n";

	this->nodes[0]->traverseTree();
	this->nodes[1]->traverseTree();
	this->nodes[2]->traverseTree();
	this->nodes[3]->traverseTree();
}

/*
int quadtree::traverseTree(Point p) {
	int level = -1;
	if (this->nodes[0] == NULL) {
		if (this->points[0].x == p.x && this->points[0].y == p.y)
			return this->level;
	}
			
	if (level == -1 && this->nodes[0] != NULL) {
		level = this->nodes[0]->traverseTree(p);
		if (level != -1)
			return level;
		else
			level = this->nodes[1]->traverseTree(p);
		if (level != -1)
			return level;
		else
			level = this->nodes[2]->traverseTree(p);
		if (level != -1)
			return level;
		else
			level = this->nodes[3]->traverseTree(p);
	}
	return level;
}*/

void quadtree::getNearestNeighbours(quadtree root, double rad, Point q) {
	std::stack<quadtree> s;
	s.push(root);
	double distance;
	std::cout<<"hi\n";
	while(!s.empty()) {
		quadtree T = s.top();
		s.pop();

		if (!T.isLeaf()) {
			for(auto C : T.getChildren()) {
				std::cout<<"in for\n";
				if (C.isLeaf()) {
					if (C.getDistance(q) < rad)
						neighboursList.push_back(C.points[0]);
					s.pop();
				}
				/*if (C.intersect(rad, q)) {
					s.push(C);
				}*/
				else
					s.push(C);
			}
		}
	}
}

std::vector<quadtree> quadtree::getChildren() {
	std::vector<quadtree> childrenList; 
	if (this->nodes[0] != NULL) {
		std::cout<<"in get children\n";
		for (int i = 0; i < 4; i++)
			childrenList.push_back(*nodes[i]);
	}
	return childrenList;
}

bool quadtree::isLeaf() {
	std::cout<<"in is leaf\n";
	if (this->nodes[0] != NULL) {
		std::cout<<"false";
		return false;
	}
	else {
		std::cout<<"true";
		return true;
	}
}
