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
    Control(State<elem> *s);
    float get_avgY();
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
float Control<elem>::get_avgY() {
	float sum = 0;
	for(auto p : state->points) {
		sum += p->get_y();
	}
	return sum/state->elements.size();
}

#endif
