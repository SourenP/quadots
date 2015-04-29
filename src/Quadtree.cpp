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

    float get_distance(float a_x, float a_y, float b_x, float b_y) {
        return sqrt(pow(a_x - a_y,2) + pow(a_x - a_y,2));
    }
    
    Quadtree(float x, float y, float width, float height);
    ~Quadtree();
    void insert(elem p);
    void traverseTree() const;
    void get_elements(vector<elem>& robjects) const;
    void get_roommates(vector<elem>& robjects, elem p) const;
    vector<elem> getNearestNeighbours(elem c, float rad);
    bool isLeaf() const;

private:
    float x;
    float y;
    int level;
    float width;
    float height;
    vector<Quadtree*> nodes;
    vector<elem> objects;

    Quadtree(int plevel, float x, float y, float width, float height);
    void split();
    bool intersects(float rad, elem c);
    int getIndex(elem p) const;
};

// CPP

template <class elem>
Quadtree<elem>::Quadtree(float x, float y, float width, float height) {
    this->level = 0;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<Quadtree*>();
    this->objects = vector<elem>();
}


template <class elem>
Quadtree<elem>::Quadtree(int pLevel, float x, float y, float width, float height) {
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
   float subWidth = (this->width / 2);
   float subHeight = (this->height / 2);
 
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
 int Quadtree<elem>::getIndex(elem p) const{
    int index = -1;

    float verMidpoint = this->x + 0.5*this->width;
    float horMidpoint = this->y + 0.5*this->height;

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
void Quadtree<elem>::get_roommates(vector<elem>& robjects, elem p) const{
    int index = getIndex(p);
    if (nodes.size()) {
        nodes[index]->get_roommates(robjects, p);
    }

    for(elem p : objects) {
        robjects.push_back(p);
    }
}

/* Use this function for testing */
template <class elem>
void Quadtree<elem>::traverseTree() const {
    for(elem p : objects)
        cout << p->get_x() << " " << p->get_y() << " at level " << level << endl;

    for(Quadtree<elem>* n : nodes)
        n->traverseTree();
}

/* Use this function for testing */
template <class elem>
void Quadtree<elem>::get_elements(vector<elem>& robjects) const {
    for(elem p : objects)
        robjects.push_back(p);
    for(Quadtree<elem>* n : nodes)
        n->get_elements(robjects);
}

template <class elem>
bool Quadtree<elem>::intersects(float rad, elem c) {
    pair<float, float> topLeft(this->x, this->y); 
    pair<float, float> botLeft(this->x, this->y + this->height);
    pair<float, float> topRight(this->x + this->width, this->y);
    pair<float, float> botRight(this->x + this->width, this->y + this->height);

    if(get_distance(topLeft.first, topLeft.second, c->get_x(), c->get_y()) < rad ||
        get_distance(botLeft.first, botLeft.second, c->get_x(), c->get_y()) < rad ||
        get_distance(topRight.first, topRight.second, c->get_x(), c->get_y()) < rad ||
        get_distance(botRight.first, botRight.second, c->get_x(), c->get_y()) < rad)
        return true;
    return false;
}

template <class elem>
vector<elem> Quadtree<elem>::getNearestNeighbours(elem c, float rad) {
    stack<Quadtree<elem>*> s;
    vector<elem> neighbors;
    s.push(this);

    while(!s.empty()) {
        Quadtree<elem> *T = s.top();
        s.pop();

        if (T->isLeaf()) {
            for (elem p : T->objects) {
                if((p->get_id() != c->get_id()) && (get_distance(p->get_x(), p->get_y(), c->get_x(), c->get_y()) < rad))
                    neighbors.push_back(p);
            }
        } else {
            for(Quadtree<elem> *C : T->nodes) {
                if (C->isLeaf()) {
                    for (elem p : C->objects)
                        if((p->get_id() != c->get_id()) && (get_distance(p->get_x(), p->get_y(), c->get_x(), c->get_y()) < rad))
                            neighbors.push_back(p);
                } else if (C->intersects(rad, c)) {
                    s.push(C);
                }
            }
        }
    }
    return neighbors;
}

template <class elem>
bool Quadtree<elem>::isLeaf() const {
    return !nodes.size(); 
}

template <class elem>
Quadtree<elem>::~Quadtree() {
    for(Quadtree<elem> *n : nodes) {
        delete n;
    }
}

#endif
