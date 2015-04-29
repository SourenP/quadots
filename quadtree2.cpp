#include "quadtree2.h"
#include "Point.h"

quadtree2::quadtree2(int pLevel, double x, double y, double width, double height) {
    this->level = pLevel;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<quadtree2>();
    this->objects = vector<Point>();
}

void quadtree2::clear() {
    objects.clear();

    for(quadtree2 n : this->nodes) {
        n.clear();
    }
}

/*
 * Splits the node into 4 subnodes
 */
 void quadtree2::split() {
   double subWidth = (this->width / 2);
   double subHeight = (this->height / 2);
 
   nodes.push_back(quadtree2(level+1, x + subWidth, y, subWidth, subHeight));
   nodes.push_back(quadtree2(level+1, x, y, subWidth, subHeight));
   nodes.push_back(quadtree2(level+1, x, y + subHeight, subWidth, subHeight));
   nodes.push_back(quadtree2(level+1, x + subWidth, y + subHeight, subWidth, subHeight));
 }

/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
 int quadtree2::getIndex(Point p) {
    int index = -1;

    double verMidpoint = this->x + 0.5*this->width;
    double horMidpoint = this->y + 0.5*this->height;

    if (p.y < horMidpoint) {
        if (p.x < verMidpoint)
            index = 0;
        else
            index = 1;
    } else {
        if (p.x > verMidpoint)
            index = 2;
        else
            index = 3;
    }

    return index;
}

/*
 * Insert the object into the quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.
 */
void quadtree2::insert(Point p) {
    if (nodes.size()) {
        int index = getIndex(p);
        if (index != -1) {
            nodes[index].insert(p);
            return;
        }
    }

    objects.push_back(p);

    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        if (!nodes.size()) { 
            split(); 
        }

        unsigned int i = 0;
        while (i < objects.size()) {
            int index = getIndex(objects[i]);
            if (index != -1) {
                nodes[index].insert(objects[i]);
                objects.erase(objects.begin() + i);
            } else {
                i++;
            }
        }
    }
}

vector<Point> quadtree2::retrieve(vector<Point> robjects, Point p) {
    int index = getIndex(p);
    if (index != -1 && nodes.size()) {
        nodes[index].retrieve(robjects, p);
    }

    copy(robjects.begin(), robjects.end(), back_inserter(objects));

    return robjects;
}

/* Use this function for testing */
void quadtree2::traverseTree() {
    if (!this->nodes.size()) {
        for (Point p : this->objects)
            cout << "At level " << this->level<< ", we have: " << p.x <<","<< p.y << endl;
        return;
    }

    cout << "not leaf" << endl;
    this->nodes[0].traverseTree();
    this->nodes[1].traverseTree();
    this->nodes[2].traverseTree();
    this->nodes[3].traverseTree();
}