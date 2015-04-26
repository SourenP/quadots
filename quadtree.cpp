#include <iostream>
#include <stdio>
#include "quadtree"
#include "Point"

/* Define constructor */
quadtree::quadtree(float x, float y, float width, float height, int level) {
	if (level == maxlevel) {
    		cout<<"Error: Can not split quadtree further.";
    		return;
  	}
	this.x = x;
	this.y = y;
	this.width = width;
	this.height = height;
	this.level = level;
	nodes = new quadtree[MAX_NODES];
}

/* Insert Point into the quadtree */
void quadtree::pushPoint(Point p) {
	if (nodes[0] != null) {		//quadtree has children
		int index = getIndex(p);	//get appropriate location for Point

		if (index != -1) {
			nodes[index].pushPoint(p);
			return;
		}
	}

	points.push_back(p);	//no children, push to parent

	if (points.size() > MAX_POINTS && level < MAX_LEVELS) {		//if no. of points in parent exceed MAX_POINTS (=1)
		if (nodes[0] == null)		//no children, so split.
			splitIntoQuads();

		int k = 0;
		while (k < points.size()) {
			Point temp = points.back();
			int index = getIndex(temp);
			if (index != -1) {
				points.pop_back();
				nodes[index] = nodes.pushPoint(temp);
			}
			else
				k++;
		}
	}
}

/* Determine which node Point belongs to.
  If a Point does not fit completely into any one node, return -1. */
int quadtree::getIndex(Point p) {
	int index = -1;
	boolean topquad, bottomquad;

	double verMidpoint = x + 0.5*width;
	double horMidpoint = y + 0.5*height;

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
	int newWidth = width/2;
	int newHeight = height/2;
	int newLevel = level + 1;

	nodes[0] = new quadtree(x, y, newWidth, newHeight, newLevel);
	nodes[1] = new quadtree(x + newWidth, y, newWidth, newHeight, newLevel);
	nodes[2] = new quadtree(x + newWidth, y + newHeight, newWidth, newHeight, newLevel);
	nodes[3] = new quadtree(x, y + newHeight, newWidth, newHeight, newLevel);
}

 


}
