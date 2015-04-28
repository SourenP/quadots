#include "Dot.h"
using namespace std;

Dot::Dot(float x, float y, float ang, float vel, unsigned int bindex)
{
	this->set_x(x);
	this->set_y(y);
	this->set_b(bindex);
	this->ang = ang;
	this->vel = vel;
}

float Dot::get_ang() {
	return this->ang;
}

float Dot::get_vel() {
	return this->vel;
}

void Dot::set_ang(float ang) {
	this->ang = ang;
}
void Dot::set_vel(float vel) {
	this->vel = vel;
}