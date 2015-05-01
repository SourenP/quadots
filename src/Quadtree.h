#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include <vector>
#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include <iostream>
#include <stack>

#define MAX_LEVELS 100
#define MAX_OBJECTS 10

using namespace std;

template <class elem>
class Quadtree {
public:

    float get_distance(float a_x, float a_y, float b_x, float b_y) {
        return sqrt(pow(a_x - b_x,2) + pow(a_y - b_y,2));
    }
    
    Quadtree(float x, float y, float width, float height);
    ~Quadtree();
    void insert(elem p);
    void traverseTree() const;
    void get_elements(vector<elem>& robjects) const;
    void get_roommates(vector<elem>& robjects, elem p) const;
    vector<elem> get_neighbours(elem c, float rad);

private:
    float x;
    float y;
    int level;
    float width;
    float height;
    vector<Quadtree*> nodes;
    vector<elem> objects;

    Quadtree(int level, float x, float y, float width, float height);
    bool isLeaf() const;
    void split();
    bool intersects(float rad, elem c);
    int getIndex(elem p) const;
};

// CPP

/*
    Create quadtree root with top left corner at coordinates x,y
*/
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

/*
    Create quadtree node at certain level
*/
template <class elem>
Quadtree<elem>::Quadtree(int level, float x, float y, float width, float height) {
    this->level = level;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->nodes = vector<Quadtree*>();
    this->objects = vector<elem>();
}

/*
    Creates four new quadtress (divides into four equal square segments) and puts them into nodes vector
*/
template <class elem>
void Quadtree<elem>::split() {
    float subWidth = (this->width / 2);
    float subHeight = (this->height / 2);

    nodes.push_back(new Quadtree<elem>(level+1, x, y, subWidth, subHeight));
    nodes.push_back(new Quadtree<elem>(level+1, x + subWidth, y, subWidth, subHeight));
    nodes.push_back(new Quadtree<elem>(level+1, x + subWidth, y + subHeight, subWidth, subHeight));
    nodes.push_back(new Quadtree<elem>(level+1, x, y + subHeight, subWidth, subHeight));
}

/*
    Determine which subtree element should be insterteed into based on position
*/
 template <class elem>
 int Quadtree<elem>::getIndex(elem p) const{
    int index;
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
    Insert element into the quadtree.
    If quadtree reaches capacity, split into subtree
    and insert elements into appropriate quadtrees.
*/
template <class elem>
void Quadtree<elem>::insert(elem p) {
    // If tree is already split
    if (!this->isLeaf()) {
        // get which node to put into
        int index = getIndex(p);
        // insert into that node
        nodes[index]->insert(p);
        return;
    }

    objects.push_back(p);

    // If quadtree exceeds capacity
    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        split();

        // Put each element into appropriate subtree
        for(elem p : objects) {
            int index = getIndex(p);
            nodes[index]->insert(p);
        }
        objects.clear();
    }
}

/*
    Get all elements that are in the same quadtree as element p.
    This only returns elements in the quadtree (not it's subtrees too).
    p will also be returned.
*/
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

/*
    Traverse tree and print out elements with what level they are at.
    Mainly for testing.
*/
template <class elem>
void Quadtree<elem>::traverseTree() const {
    // print out elements
    for(elem p : objects)
        cout << p->get_x() << " " << p->get_y() << " at level " << level << endl;

    // traverse subtrees
    for(Quadtree<elem>* n : nodes)
        n->traverseTree();
}

/*
    Get all the elements in the quadtree.
    This includes the elements of all its subtrees.
*/
template <class elem>
void Quadtree<elem>::get_elements(vector<elem>& robjects) const {
    for(elem p : objects)
        robjects.push_back(p);
    for(Quadtree<elem>* n : nodes)
        n->get_elements(robjects);
}

/*
    Return true if this quadtree intersecs with the area
    formed by a square around c with the lenght rad.
    Used for nearest neighbors.
*/
template <class elem>
bool Quadtree<elem>::intersects(float rad, elem c) {
    pair<float, float> P1(this->x, this->y); 
    pair<float, float> P2(this->x + this->width, this->y + this->height);
    pair<float, float> P3(c->get_x()-rad, c->get_y()-rad); 
    pair<float, float> P4(c->get_x()+rad, c->get_y()+rad);

    float rect_a_right = P2.first;
    float rect_a_left = P1.first;
    float rect_a_top = P2.second;
    float rect_a_bot = P1.second;

    float rect_b_right = P4.first;
    float rect_b_left = P3.first;
    float rect_b_top = P4.second;
    float rect_b_bot = P3.second;
    
    bool seperate = rect_a_right < rect_b_left || rect_a_left > rect_b_right || rect_a_top < rect_b_bot || rect_a_bot > rect_b_top;
    return !seperate;
}

/*
    Gets all neighbors of element c in the radius rad.
*/
template <class elem>
vector<elem> Quadtree<elem>::get_neighbours(elem c, float rad) {
    // Maintain a stack of all quadtrees whose elements will be compared
    stack<Quadtree<elem>*> s;
    vector<elem> neighbors;

    // Push root onto stack
    s.push(this);

    while(!s.empty()) {
        Quadtree<elem> *T = s.top();
        s.pop();

        // If T is a leaf, check if the elements in it lie in the radius
        if (T->isLeaf()) {
            for (elem p : T->objects) {
                if((p->get_id() != c->get_id()) && (get_distance(p->get_x(), p->get_y(), c->get_x(), c->get_y()) < rad))
                    neighbors.push_back(p);
            }
        } else {
            // For all subtrees, push onto the stack those that intersect with the area around c that is being considered.
            for(Quadtree<elem> *C : T->nodes) {
                if (C->isLeaf()) {
                    for (elem p : C->objects) {
                        if((p->get_id() != c->get_id()) && (get_distance(p->get_x(), p->get_y(), c->get_x(), c->get_y()) < rad))
                            neighbors.push_back(p);
                    }
                } else if (C->intersects(rad, c)) {
                    s.push(C);
                }
            }
        }
    }
    return neighbors;
}

/*
    Return true if quadtree has no children.
*/
template <class elem>
bool Quadtree<elem>::isLeaf() const {
    return !nodes.size(); 
}

/*
    Destructor.
    Delete all subtrees.
*/
template <class elem>
Quadtree<elem>::~Quadtree() {
    for(Quadtree<elem> *n : nodes) {
        delete n;
    }
}

#endif
