#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <vector>
#include <math.h>
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
    vector<shared_ptr<elem>> neighbors(const shared_ptr<elem> a, float rad);
    float get_avgY();
    float get_com_x();
    float get_com_y();
    float get_ncom_x(const Elem_p a);
	float get_ncom_y(const Elem_p a);
	float get_avg_d(const Elem_p a);
	float dir_towards(const Elem_p a, float x, float y);
	float random_pos(int minx, int miny);
    void setState(State<elem> *s);
private:
	State<elem> *state;
};

// CPP

template <class elem>
Control<elem>::Control(State<elem> *s)
{
	this->state = s;
	srand(time(NULL));
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
vector<shared_ptr<elem>> Control<elem>::neighbors(const shared_ptr<elem> a, float rad) {
	vector<shared_ptr<elem>> nearest_e;
	for(auto e : state->elements) {
		if(e->get_id() != a->get_id()) {
			if(get_distance(e, a) < rad) {
				nearest_e.push_back(e);
			}
		}
	}
	return nearest_e;
}

template <class elem>
float Control<elem>::get_com_x() {
	float sum;
	for(auto e : state->elements) {
		sum += e->get_x();
	}
	return sum/state->elements.size();
}

template <class elem>
float Control<elem>::get_com_y() {
	float sum;
	for(auto e : state->elements) {
		sum += e->get_y();
	}
	return sum/state->elements.size();
}

template <class elem>
float Control<elem>::get_ncom_x(const Elem_p a) {
	float sum;
	for(auto e : state->elements)
		if(e->get_id() != a->get_id())
			sum += e->get_x();
	return sum/(state->elements.size()-1);
}

template <class elem>
float Control<elem>::get_ncom_y(const Elem_p a) {
	float sum;
	for(auto e : state->elements)
		if(e->get_id() != a->get_id())
			sum += e->get_y();
	return sum/(state->elements.size()-1);
}

template <class elem>
float Control<elem>::get_avg_d(const Elem_p a) {
	float sum;
	for(auto e : state->elements)
		if(e->get_id() != a->get_id())
			sum += e->get_ang();
	return sum/(state->elements.size()-1);
}

template <class elem>
float Control<elem>::dir_towards(const Elem_p a, float x, float y) {
	float ratio = (y - a->get_y()) / (x - a->get_x());
	float ang = atan(ratio) * 180.0 / M_PI;
	return (a->get_x() <= x) ? ang : (ang +180);
}

template <class elem>
float Control<elem>::get_distance(const Elem_p a, const Elem_p b) {
    return sqrt(pow(a->get_x() - b->get_x(),2) + pow(a->get_y() - b->get_y(),2));
}

template <class elem>
float Control<elem>::random_pos(int min, int max) {
	return(float) (rand() % max + min);
}

#endif
