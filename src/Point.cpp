#include "Point.h"
using namespace std;

Point::Point(float x, float y, float ang, float vel, int bindex)
{
	this->x = x;
	this->y = y;
	this->ang = ang;
	this->vel = vel;
	this->bindex = bindex;
}