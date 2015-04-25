#include <iostream>
#include <stdio>
#include "quadtree"
#include "Point"

/* Define constructor */
quadtree::quadtree(float x, float y, int level) {
	if (level == maxlevel) {
    		cout<<"Error: Can not split quadtree further.";
    		return;
  	}
	this.x = x;
	this.y = y;
	this.level = level;
	nodes = new quadtree[MAX_NODES];
}

void quadtree::pushPoint(Point p) {
	if (nodes[0] != null) {		//quadtree has children
		int index = getIndex(p);	//get appropriate location for Point

		if (index != -1) {
			nodes[index].pushPoint(p);
			return;
		}
	}

	points.push_back(p);	//no children, push to parent

	if (points.size() > MAX_POINTS && level < MAX_LEVELS) {
		if (nodes[0] == null)		//no children, so split.
			split();
	}

}

quadtree::getNeighbouringPoints(float xcor, float ycor) {
  vector<Point> neighbourList;

  /* Add checks for if the p exists or not - IMPORTANT!!! */
  neighbourList.push_back(getPointsAt(xcor-1, ycor-1));
  neighbourList.push_back(getPointsAt(xcor-1, ycor));
  neighbourList.push_back(getPointsAt(xcor-1, ycor+1));
  neighbourList.push_back(getPointsAt(xcor, ycor-1));
  neighbourList.push_back(getPointsAt(xcor, ycor+1));
  neighbourList.push_back(getPointsAt(xcor+1, ycor-1));
  neighbourList.push_back(getPointsAt(xcor+1, ycor));
  neighbourList.push_back(getPointsAt(xcor+1, ycor+1));

  return neighbourList;
}

vector<Point> quadtree::getPointsAt(float x1, float y1) {
  /* confused about this, have to think. */
	if (level == maxlevel)
		return points; 

	vector<Point> returnpoints, childReturnpoints;
	//belongs to 
	if (!points.empty()) {
		returnps = points;
	}
	if (x1 > xcor + width / 2.0f && x1 < xcor + width) {
		if (y1 > ycor + height / 2.0f && y1 < ycor + height) {
			childReturnps = SE->GetPointsAt(x1, y1);
			returnps.insert(returnps.end(), childReturnps.begin(), childReturnps.end());
			return returnps;
		}
		else if (y1 > ycor && y1 <= ycor + height / 2.0f) {
			childReturnps = NE->GetpsAt(x1, y1);
			returnps.insert(returnps.end(), childReturnps.begin(), childReturnps.end());
			return returnps;
		}
	}
	else if (x1 > x && x1 <= x + width / 2.0f) {
		if (y1 > ycor + height / 2.0f && y1 < ycor + height) {
			childReturnps = SW->GetpsAt(x1, y1);
			returnps.insert(returnps.end(), childReturnps.begin(), childReturnps.end());
			return returnps;
		}
		else if (y1 > ycor && y1 <= ycor + height / 2.0f) {
			childReturnps = NW->GetpsAt(x1, y1);
			returnps.insert(returnps.end(), childReturnps.begin(), childReturnps.end());
			return returnps;
		}
	}

	return returnps;
}

}

//check if point lies in the passed node
bool Quadtree::contains(Quadtree *child,Point *p) {
	return	 !(p->x < child->x ||
		p->y < child->y ||
		p->x > child->x + child->width ||
		p->y > child->y + child->height ||
		p->x + p->width < child->x ||
		p->y + p->height < child->y ||
		p->x + p->width > child->x + child->width ||
		p->y + p->height > child->y + child->height);
}



