/* Header file for quadtree library */
#ifndef __QUADTREE_H
#define __QUADTREE_H

#include <vector>
#include "Point"  //include Point library made by Souren

/* Quadtree will consist of levels which will have a certain width and height and a number associated.
Each level will consist of a vector of Points. 
The quadtree library will also have pointer to its parent node and 4 children nodes. 
Each level can not have more than 4 nodes. */

class quadtree {
public:
  quadtree(float xcor, float ycor, int state, float width, float height, int level, int maxlevel);  //constructor
  ~quadtree();  //destructor
  
  void pushPoint(Point p);
  vector<Point> getNeighbouringPoints(float xcor, float ycor);
  vector<Point> getPointsAt(float x, float y);

private:
  float xcor;
  float ycor;
  int state;
  float width;
  float height;
  int level;
  int maxlevel;
  
  vector<Point> points;
  
  quadtree* parent;
  quadtree* topleft;
  quadtree* topright;
  quadtree* bottomright;

};

