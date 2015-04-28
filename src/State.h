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
    State(const State<elem>& other);
    vector<shared_ptr<elem>> elements;
private:
};

// CPP

template <class elem>
State<elem>::State() {};

template <class elem>
State<elem>::State(const State<elem>& other)
{
	cout << "copy time" << endl;
	if (this != &other) // protect against invalid self-assignment
	{
		elements.clear();
		cout << elements.size() << endl;
		for(auto e : other.elements) {
			shared_ptr<elem> new_element_p(new elem(*e));
    		elements.push_back(new_element_p);
		}		
	}
}

template <class elem>
ostream& operator<<(ostream &os, const State<elem>& s)
{
	os << "[\n";
	for (shared_ptr<elem> p : s.elements)
		os << "\t(" << p->get_x() << ", " << p->get_y() << ")\n";
	os << "]\n";

	return os;
}
#endif