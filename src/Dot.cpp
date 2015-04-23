#include "Dot.h"
#include "Space.h"
using namespace std;

Dot::Dot(float x, float y, array<int8_t,4> color, float ang, float vel, int type, Space *s)
{
	this->x = x;
	this->y = y;
	this->color = color;
	this->ang = ang;
	this->vel = vel;
	this->type = type;
	this->s = s;
}