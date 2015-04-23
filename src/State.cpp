#include "State.h"
using namespace std;

State::State() {};

ostream& operator<<(ostream &os, const State& s)
{
	os << "[\n";
	for (Point::Point_p p : s.points)
		os << "\t(" << p->x << ", " << p->y << ")\n";
	os << "]\n";

	return os;
}