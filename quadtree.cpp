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

quadtree::pushPoint(Point p) {
  this.points.push_back(p); //push Point p to vector of Point(s)
}

quadtree::getNeighbouringPoints(float xcor, float ycor) {
  vector<Point> neighbourList;

  /* Add checks for if the object exists or not - IMPORTANT!!! */
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

quadtree::getPointsAt(float xcor, float ycor) {
  /* confused about this, have to think. */
}



