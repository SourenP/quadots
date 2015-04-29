#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

template <class elem> class State
{
public:
    State(double width, double height);
    //State(const State<elem>& other);
    ~State();
    vector<shared_ptr<elem>> get_elements();
    void add(shared_ptr<elem> p);
    Quadtree<shared_ptr<elem>> *elemTree;
private:
};

// CPP

template <class elem>
State<elem>::State(double width, double height) {
	elemTree = new Quadtree<shared_ptr<elem>>(0, 0, width, height);
}

template <class elem>
State<elem>::~State() {
	delete elemTree;
}

template <class elem>
vector<shared_ptr<elem>> State<elem>::get_elements() {
	vector<shared_ptr<elem>> elements;
	elemTree->get_elements(elements);
	return elements;
}

template <class elem>
void State<elem>::add(shared_ptr<elem> p) {
	elemTree->insert(p);
}

template <class elem>
ostream& operator<<(ostream &os, const State<elem>& s)
{
	vector<shared_ptr<elem>> elements = s->get_elements();
	os << "[\n";
	for (shared_ptr<elem> p : elements)
		os << "\t(" << p->get_x() << ", " << p->get_y() << ")\n";
	os << "]\n";

	return os;
}
#endif