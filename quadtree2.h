/* Header file for quadtree library */
#ifndef __QUADTREE2_H
#define __QUADTREE2_H

#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include <iostream>
#include "Point.h"  //include Point library made by Souren

/* Quadtree will consist of levels which will have a certain width and height and a number associated.
Each level will consist of a vector of Points. 
The quadtree library will also have pointer to its parent node and 4 children nodes. 
Each level can not have more than 4 nodes. */

#define MAX_LEVELS 5
#define MAX_OBJECTS 5

using namespace std;

class quadtree2 {
public:
    quadtree2(int plevel, double x, double y, double width, double height);  //constructor
    void insert(Point p);
    void clear();
    void traverseTree();

private:

    double x;
    double y;
    int level;
    double width;
    double height;
    vector<quadtree2> nodes;
    vector<Point> objects;

    void split();
    int getIndex(Point p);
    vector<Point> retrieve(vector<Point> robjects, Point p);
};

#endif
