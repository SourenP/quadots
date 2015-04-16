#include <iostream>
#include <stdio>
#include "quadtree"
#include "Point"

#define DEAD_STATE 0

/* Define constructor */
quadtree::quadtree(float xcor, float ycor, int state, float width, float height, int level, int maxlevel) {
  if (level == maxlevel) {
    cout<<"Error: Can not split quadtree further.";
    return;
  }

  this.xcor = xcor;
  this.ycor = ycor;
  this.state = state;
  this.width = width;
  this.height = height;
  this.level = level;
  this.maxlevel = maxlevel;

  topleft = new Quadtree(xcor, ycor, DEAD_STATE, width/2, height/2, level+1, maxLevel);
  topright = new Quadtree(xcor + width/2, ycor, DEAD_STATE, width/2, height/2, level+1, maxLevel);
  bottomleft = new Quadtree(xcor, ycor + height/2, DEAD_STATE, width/2, height/2, level+1, maxLevel);
  bottomright = new Quadtree(xcor + width/2, ycor + height/2, DEAD_STATE, width/2, height/2, level+1, maxLevel);
}

/* Define destructor */
quadtree::~quadtree() {
  if (level == maxlevel)
    return;

  delete topleft;
  delete topright;
  delete bottomleft;
  delete bottomright;
}

void quadtree::pushPoint(Point p) {
	//belongs to parent
	if (level == maxlevel){
		this.points.push_back(p); //push Point p to vector of Point(s)
		return;
	}

	//else check inner nodes
	if (contains(NW, p)) {
		NW->pushPoint(p); return;
	}
	else if (contains(NE, p)) {
		NE->pushPoint(p); return;
	}
	else if (contains(SW, p)) {
		SW->pushPoint(p); return;
	}
	else if (contains(SE, p)) {
		SE->pushPoint(p); return;
	}
	if (contains(this, p)) {
		this.points.push_back(p);
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



