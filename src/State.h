#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
#include "Quadtree.h"
using namespace std;

// Declaration

template <class elem> 
class State {
public:
    State(float width, float height);
    ~State();
    const vector<shared_ptr<elem>> get_elements() const;
    const vector<shared_ptr<elem>> qneighbors(shared_ptr<elem> p, float radius) const;
    void add(shared_ptr<elem> p);
private:
	Quadtree<shared_ptr<elem>> *elemTree;
};

// Definition

/*
	Constructor
	Creates the quadtree.
*/
template <class elem>
State<elem>::State(float width, float height) {
	this->elemTree = new Quadtree<shared_ptr<elem>>(0, 0, width, height);
}

/*
	Destructor
	Deletes the quadtree.
*/
template <class elem>
State<elem>::~State() {
	delete elemTree;
}

/*
	Returns a vector of the elements the state currently contains.
*/
template <class elem>
const vector<shared_ptr<elem>> State<elem>::get_elements() const {
	vector<shared_ptr<elem>> elements;
	elemTree->get_elements(elements);
	return elements;
}

/*
	Gets all neighbors of element a in the radius by checking all elements (brute force).
	Calls get_neighbors of the quadtree.
*/
template <class elem>
const vector<shared_ptr<elem>> State<elem>::qneighbors(shared_ptr<elem> p, float radius) const {
	return elemTree->get_neighbours(p, radius);
}

/*
	Add an element to the state.
	Calls instert of the quadtree.
*/
template <class elem>
void State<elem>::add(shared_ptr<elem> p) {
	elemTree->insert(p);
}


/*
	Print out the state in format:
	[
		(1st element x, 1st element y)
		(2nd element x, 2nd element y)
		.
		.
		.
	]
*/
template <class elem>
ostream& operator<<(ostream &os, State<elem>& s)
{
	vector<shared_ptr<elem>> elements = s.get_elements();
	os << "[\n";
	for (shared_ptr<elem> p : elements)
		os << "\t(" << p->get_x() << ", " << p->get_y() << ")\n";
	os << "]\n";

	return os;
}
#endif