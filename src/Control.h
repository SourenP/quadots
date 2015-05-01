#ifndef CONTROL_H
#define CONTROL_H

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include "State.h"
#include "Dot.h"
using namespace std;

template <class elem>
class Control
{
public:
	typedef shared_ptr<elem> Elem_p;

    Control(State<elem> *s);
    void setState(State<elem> *s);

    float get_distance(const Elem_p a,const Elem_p b) const;
    float avg_x() const;
    float avg_x(const vector<Elem_p> elements) const;
    float avg_y() const;
    float avg_y(const vector<Elem_p> elements) const;
    float random_pos(int minx, int miny);

	vector<Elem_p> qneighbors(Elem_p a, float radius);
	vector<Elem_p> neighbors(const Elem_p a, float radius);
	
    // Specific to Dots
	float avg_dir() const;
	float avg_dir(const vector<Elem_p> elements) const;
	float dir_towards(const Elem_p a, float x, float y) const;
private:
	State<elem> *state;
};

// CPP

/*
	Constructor for Control
	srand is for the function random_pos.
*/
template <class elem>
Control<elem>::Control(State<elem> *s)
{
	this->state = s;
	srand(time(NULL)); // For random_pos
}

/*
	Sets the current state of the control.
	Does not take care of the lifetime of the state.
*/
template <class elem>
void Control<elem>::setState(State<elem> *s) {
	this->state = s;
}

/*
	Returns average x of all elements in state.
*/
template <class elem>
float Control<elem>::avg_x() const {
	float sum = 0;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_x();
	return sum/elements.size();
}

/*
	Returns average x of all elements in elements vector.
*/
template <class elem>
float Control<elem>::avg_x(const vector<Elem_p> elements) const {
	float sum = 0;
	for(auto e : elements)
		sum += e->get_x();
	return sum/elements.size();
}

/*
	Returns average y of all elements in state.
*/
template <class elem>
float Control<elem>::avg_y() const {
	float sum = 0;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_y();
	return sum/elements.size();
}

/*
	Returns average y of all elements in elements vector.
*/
template <class elem>
float Control<elem>::avg_y(const vector<Elem_p> elements) const {
	float sum = 0;
	for(auto e : elements)
		sum += e->get_y();
	return sum/elements.size();
}

/*
	Returns distance from element a to element b.
*/
template <class elem>
float Control<elem>::get_distance(const Elem_p a, const Elem_p b) const {
    return sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
}

/*
	Returns a random float in the range [min,max).
*/
template <class elem>
float Control<elem>::random_pos(int min, int max) {
	return(float) (rand() % max + min);
}

/*
	Gets all neighbors of element a in the radius defined by using the quadtree in state.
*/
template <class elem>
vector<typename Control<elem>::Elem_p> Control<elem>::qneighbors(Elem_p a, float radius) {
	return state->qneighbors(a, radius);
}

/*
	Gets all neighbors of element a in the radius by checking all elements (brute force).
*/
template <class elem>
vector<typename Control<elem>::Elem_p> Control<elem>::neighbors(const Elem_p a, float radius) {
	vector<Elem_p> nearest_e;
	for(auto e : state->elements) {
		if(e->get_id() != a->get_id()) {
			if(get_distance(e, a) < radius) {
				nearest_e.push_back(e);
			}
		}
	}
	return nearest_e;
}

// Specific to Dots

template <class elem>
float Control<elem>::avg_dir() const {
	return 0;
}
/*
	Returns average dirrection of all Dots in state.
*/
template <>
float Control<Dot>::avg_dir() const {
	float sum = 0;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_ang();
	return sum/elements.size();
}

template <class elem>
float Control<elem>::avg_dir(const vector<Elem_p> elements) const {
	return 0;
}

/*
	Returns average direction of all Dots in elements vector.
*/
template <>
float Control<Dot>::avg_dir(const vector<Dot::Dot_p> elements) const {
	float sum = 0;
	for(auto e : elements)
		sum += e->get_ang();
	return sum/(elements.size());
}

template <class elem>
float Control<elem>::dir_towards(const Elem_p a, float x, float y) const {
	return 0;
}

/*
	Returns direction Dot a should have to be facing the point at coordinates x,y.
*/
template <>
float Control<Dot>::dir_towards(const Dot::Dot_p a, float x, float y) const {
	float ratio = (y - a->get_y()) / (x - a->get_x());
	float ang = atan(ratio) * 180.0 / M_PI;
	return (a->get_x() <= x) ? ang : (ang + 180);
}

#endif
