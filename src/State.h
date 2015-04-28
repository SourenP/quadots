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
    State();
    //friend ostream& operator<<(ostream &os, const State<elem>& s);
    vector<shared_ptr<elem>> elements;
private:
};

// CPP

template <class elem>
State<elem>::State() {};

#endif
/*
ostream& operator<<(ostream &os, const State<elem>& s)
{
	os << "[\n";
	for (shared_ptr<elem> p : s.elements)
		os << "\t(" << p->get_x() << ", " << p->get_y() << ")\n";
	os << "]\n";

	return os;
}
*/