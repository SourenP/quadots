#include "Point.h"
using namespace std;

int Point::nextID = 0;

Point::Point() {};

Point::Point(float x, float y, int bindex)
{
	this->x = x;
	this->y = y;
	this->bindex = bindex;
	this->id = ++(this->nextID);
}

int Point::get_id() const {
	return this->id;
}

float Point::get_x() const {
	return this->x;
}

float Point::get_y() const {
	return this->y;
}

int Point::get_b() const {
	return this->bindex;
}

void Point::set_x(float x) {
	this->x = x;
}
void Point::set_y(float y) {
	this->y = y;
}

void Point::set_b(int bindex) {
	this->bindex = bindex;
}

void Point::update() {
	return;
}