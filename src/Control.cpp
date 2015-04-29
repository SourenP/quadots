#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <vector>
#include <math.h>
#include <iostream>
#include "State.cpp"
using namespace std;

template <class elem>
class Control
{
public:
	typedef shared_ptr<elem> Elem_p;

    Control(State<elem> *s);

    float get_distance(const Elem_p a,const Elem_p b) const;

    float com_x() const;
    float com_x(const vector<Elem_p> elements) const;

    float com_y() const;
    float com_y(const vector<Elem_p> elements) const;

	float avg_dir() const;
	float avg_dir(const vector<Elem_p> elements) const;

	float dir_towards(const Elem_p a, float x, float y) const;

	vector<Elem_p> qneighbors(Elem_p a, float range);

	//vector<Elem_p> neighbors(const Elem_p a, float range) const;

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
float Control<elem>::com_x() const {
	float sum;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_x();
	return sum/state->elements.size();
}

template <class elem>
float Control<elem>::com_x(const vector<Elem_p> elements) const {
	float sum;
	for(auto e : elements)
		sum += e->get_x();
	return sum/state->elements.size();
}

template <class elem>
float Control<elem>::com_y() const {
	float sum;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_y();
	return sum/state->elements.size();
}

template <class elem>
float Control<elem>::com_y(const vector<Elem_p> elements) const {
	float sum;
	for(auto e : elements)
		sum += e->get_y();
	return sum/state->elements.size();
}


template <class elem>
float Control<elem>::avg_dir() const {
	float sum;
	vector<Elem_p> elements = state->get_elements();
	for(auto e : elements)
		sum += e->get_ang();
	return sum/(elements.size());
}

template <class elem>
float Control<elem>::avg_dir(const vector<Elem_p> elements) const {
	float sum;
	for(auto e : elements)
		sum += e->get_ang();
	return sum/(elements.size());
}


template <class elem>
float Control<elem>::dir_towards(const Elem_p a, float x, float y) const {
	float ratio = (y - a->get_y()) / (x - a->get_x());
	float ang = atan(ratio) * 180.0 / M_PI;
	return (a->get_x() <= x) ? ang : (ang +180);
}

template <class elem>
float Control<elem>::get_distance(const Elem_p a, const Elem_p b) const {
    return sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
}


template <class elem>
vector<shared_ptr<elem>> Control<elem>::qneighbors(shared_ptr<elem> a, float range) {
	return state->get_neighbors(a->x, a->y, range);
}

/*
/// REWRITE TO GET ALL IN RADIUS
template <class elem>
Elem_p Control<elem>::get_nearest(const shared_ptr<elem> a) {
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
*/

#endif
