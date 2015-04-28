#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Point.h"
#include "State.h"
using namespace std;

template <class elem>
class Control
{
public:
	typedef shared_ptr<elem> Elem_p;
    Control(State<elem> *s);
    float get_distance(const Elem_p a,const Elem_p b);
    Elem_p get_nearest(const Elem_p a);
    float get_avgY();

    void setState(State<elem> *s);
private:
	State<elem> *state;
};

// CPP

template <class elem>
Control<elem>::Control(State<elem> *s)
{
	this->state = s;
}

template <class elem>
void Control<elem>::setState(State<elem> *s) {
	this->state = s;
}

template <class elem>
float Control<elem>::get_avgY() {
	float sum = 0;
	for(auto e : state->elements) {
		sum += e->get_y();
	}
	return sum/state->elements.size();
}

template <class elem>
shared_ptr<elem> Control<elem>::get_nearest(const shared_ptr<elem> a) {
	float dist = -1;
	float curr_dist;
	shared_ptr<elem> nearest_e = nullptr;
	for(auto e : state->elements) {
		if(e->get_id() != a->get_id()) {
			curr_dist = get_distance(e, a);
			if(curr_dist > dist) {
				dist = curr_dist;
				nearest_e = e;
			}
		}
	}
	return nearest_e;
}

template <class elem>
float Control<elem>::get_distance(const Elem_p a, const Elem_p b) {
    return sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
}

#endif
