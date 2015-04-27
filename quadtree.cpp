#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include "quadtree.h"
#include "Point.h"

quadtree::quadtree(double x, double y, double width, double height, int level) {
	if (this->level == MAX_LEVELS) {
    		std::cout<<"Error: Can not split quadtree further.";
    		return;
  	}
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->level = level;
	this->split = false;
}

void quadtree::pushPoint(Point p) {
	if (split == true) {		//quadtree has children
		int index = getIndex(p);	//get appropriate location for Point

		if (index != -1) {
			nodes[index]->pushPoint(p);
			return;
		}
	}
	points.push_back(p);	//no children, push to parent

	if (points.size() > MAX_POINTS && level < MAX_LEVELS) {		//if no. of points in parent exceed MAX_POINTS (=1)
		if (split == false)		//no children, so split.
			splitIntoQuads();

		int k = 0;
		while (k < points.size()) {
			Point temp = points.back();
			int index = getIndex(temp);
			if (index != -1) {
				points.pop_back();
				nodes[index]->pushPoint(temp);
			}
			else
				k++;
		}
	}
}

int quadtree::getIndex(Point p) {
	int index = -1;
	bool topquad, bottomquad;

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

void quadtree::splitIntoQuads() {
	int newWidth = this->width/2;
	int newHeight = this->height/2;
	int newLevel = this->level + 1;

	nodes[0] = new quadtree(x, this->y, newWidth, newHeight, newLevel);
	nodes[1] = new quadtree(this->x + newWidth, this->y, newWidth, newHeight, newLevel);
	nodes[2] = new quadtree(this->x + newWidth, this->y + newHeight, newWidth, newHeight, newLevel);
	nodes[3] = new quadtree(this->x, this->y + newHeight, newWidth, newHeight, newLevel);

	this->split = true;
}

void quadtree::clearQuadtree() {
	std::cout<<"clear\n";
	if (split == false) {
		points.erase(points.end() - 1);		//start erasing from the end
		return;
	}

	for (int i = 0; i < MAX_NODES; i++) {
		if (split == true) {
			nodes[i]->clearQuadtree();
			nodes[i] = NULL;
		}
	}
	this->split = false;
}

int quadtree::traverseTree(quadtree* q, Point p) {
	int found = 0;
	if (split == false) {		//calling node has no children
		if (this->x == p.x && this->y == p.y)
			return this->level; 
		else
			return -1;	//point not found
	}
	else if (split == true) {
		found = traverseTree(nodes[0], p);
		if (found == -1)
			found = traverseTree(nodes[1], p);
		if (found == -1)
			found = traverseTree(nodes[2], p);
		if (found == -1)
			found = traverseTree(nodes[3], p);
	}
	return found;
}

std::vector<Point> quadtree::getNearestNeighbours(Point p) {
	int level = traverseTree(this, p);
	std::vector<Point> nearest_points = getPointsAtLevel(level - 1);
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
}

std::vector<Point> quadtree::getPointsAtLevel(int level) {
	std::vector<Point> temp;
	return temp;	
}

double quadtree::getDistance(Point p1, Point p2) {
	return (int)sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));	
}

