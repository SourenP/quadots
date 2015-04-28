#include "State.h"
using namespace std;

template <class elem>
State<elem>::State() {};

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