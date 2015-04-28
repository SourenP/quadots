#include "Control.h"
using namespace std;

template <class elem>
Control<elem>::Control(State<elem> *s)
{
	this->state = s;
}

template <class elem>
float Control<elem>::get_avgY() {
	float sum = 0;
	for(auto p : state->points) {
		sum += p->get_y();
	}
	return sum/state->elements.size();
}