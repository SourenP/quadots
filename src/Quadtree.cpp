/* Header file for Quadtree library */
#ifndef QUADTREE_CPP
#define QUADTREE_CPP

#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include <iostream>
#include <stack>

/* Quadtree will consist of levels which will have a certain width and height and a number associated.
Each level will consist of a vector of Points. 
The Quadtree library will also have pointer to its parent node and 4 children nodes. 
Each level can not have more than 4 nodes. */

#define MAX_LEVELS 100
#define MAX_OBJECTS 1

using namespace std;

template <class elem>
class Quadtree {
public:

    float get_distance(pair<float, float> a, pair<float, float> b) {
        return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second,2));
    }
    
    Quadtree(double x, double y, double width, double height);
    ~Quadtree();
    void insert(elem p);
    void traverseTree();
    void get_elements(vector<elem>& robjects);
    void retrieve(vector<elem>& robjects, elem p);
    vector<elem> getNearestNeighbours(float rad, pair<float, float> c);
    bool isLeaf();

private:
    double x;
    double y;
    int level;
    double width;
    double height;
    vector<Quadtree*> nodes;
    vector<elem> objects;

    Quadtree(int plevel, double x, double y, double width, double height);
    void split();
    bool intersects(double radius, pair<float, float> c);
    int getIndex(elem p);
};

// CPP

template <class elem>
Quadtree<elem>::Quadtree(double x, double y, double width, double height) {
    this->level = 0;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<Quadtree*>();
    this->objects = vector<elem>();
}


template <class elem>
Quadtree<elem>::Quadtree(int pLevel, double x, double y, double width, double height) {
    this->level = pLevel;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<Quadtree*>();
    this->objects = vector<elem>();
}

/*
 * Splits the node into 4 subnodes
 */
 template <class elem>
 void Quadtree<elem>::split() {
   double subWidth = (this->width / 2);
   double subHeight = (this->height / 2);
 
   nodes.push_back(new Quadtree<elem>(level+1, x + subWidth, y, subWidth, subHeight));
   nodes.push_back(new Quadtree<elem>(level+1, x, y, subWidth, subHeight));
   nodes.push_back(new Quadtree<elem>(level+1, x, y + subHeight, subWidth, subHeight));
   nodes.push_back(new Quadtree<elem>(level+1, x + subWidth, y + subHeight, subWidth, subHeight));
 }

/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
 template <class elem>
 int Quadtree<elem>::getIndex(elem p) {
    int index = -1;

    double verMidpoint = this->x + 0.5*this->width;
    double horMidpoint = this->y + 0.5*this->height;

    if (p->get_y() < horMidpoint) {
        if (p->get_x() < verMidpoint)
            index = 0;
        else
            index = 1;
    } else {
        if (p->get_x() > verMidpoint)
            index = 2;
        else
            index = 3;
    }

    return index;
}

/*
 * Insert the object into the Quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.
 */
template <class elem>
void Quadtree<elem>::insert(elem p) {
    // If tree is already split
    if (nodes.size()) {
        // get which node to put into
        int index = getIndex(p);
        // insert into that node
        nodes[index]->insert(p);
        return;
    }

    objects.push_back(p);
    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        split();
        for(elem p : objects) {
            int index = getIndex(p);
            nodes[index]->insert(p);
        }
        objects.clear();
    }
}

template <class elem>
void Quadtree<elem>::retrieve(vector<elem>& robjects, elem p) {
    int index = getIndex(p);
    if (nodes.size()) {
        nodes[index]->retrieve(robjects, p);
    }

    for(elem p : objects) {
        robjects.push_back(p);
    }
}

/* Use this function for testing */
template <class elem>
void Quadtree<elem>::traverseTree() {
    for(elem p : objects)
        cout << p->get_x() << " " << p->get_y() << " at level " << level << endl;

    for(Quadtree<elem>* n : nodes)
        n->traverseTree();
}

/* Use this function for testing */
template <class elem>
void Quadtree<elem>::get_elements(vector<elem>& robjects) {
    for(elem p : objects)
        robjects.push_back(p);
    for(Quadtree<elem>* n : nodes)
        n->get_elements(robjects);
}

template <class elem>
bool Quadtree<elem>::intersects(double rad, pair<float, float> c) {
    pair<float, float> topLeft(this->x, this->y); 
    pair<float, float> botLeft(this->x, this->y + this->height);
    pair<float, float> topRight(this->x + this->width, this->y);
    pair<float, float> botRight(this->x + this->width, this->y + this->height);

    if(get_distance(topLeft, c) < rad ||
        get_distance(botLeft, c) < rad ||
        get_distance(topRight, c) < rad ||
        get_distance(botRight, c) < rad )
        return true;
    return false;
}

template <class elem>
vector<elem> Quadtree<elem>::getNearestNeighbours(float rad, pair<float, float> c) {
    stack<Quadtree<elem>*> s;
    vector<elem> neighbors;
    s.push(this);

    while(!s.empty()) {
        Quadtree<elem> *T = s.top();
        s.pop();

        if (T->isLeaf()) {
            for (elem p : T->objects) {
                if(get_distance(make_pair(p->get_x(), p->get_y()), c) < rad) {
                    neighbors.push_back(p);
                }
            }
        } else {
            for(Quadtree<elem> *C : T->nodes) {
                if (C->isLeaf()) {
                    for (elem p : C->objects)
                        if(get_distance(make_pair(p->get_x(), p->get_y()), c) < rad)
                            neighbors.push_back(p);
                }
                else if (C->intersects(rad, c)) {
                    cout << C->level << endl;
                    s.push(C);
                }
            }
        }
    }
    return neighbors;
}

template <class elem>
bool Quadtree<elem>::isLeaf() {
    return !nodes.size(); 
}

template <class elem>
Quadtree<elem>::~Quadtree() {
    for(Quadtree<elem> *n : nodes) {
        delete n;
    }
}

#endif
