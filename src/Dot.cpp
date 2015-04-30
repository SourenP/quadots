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
	if (ang> 360.0) {
		ang = 360 - ang;
	} else if (ang < 0) {
		ang = 360 + ang;
	}
	this->ang = ang;
}
void Dot::set_vel(float vel) {
	this->vel = vel;
}

void Dot::update() {
    // Update location based on angle and velocity
    this->set_x(this->get_x() + cos(this->get_ang() * PI/180.0) * this->get_vel());
    this->set_y(this->get_y() + sin(this->get_ang() * PI/180.0) * this->get_vel());
}