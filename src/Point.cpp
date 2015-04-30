 #include "Point.h"
using namespace std;

int Point::nextID = 0;

Point::Point() {};

Point::Point(float x, float y, unsigned int bindex)
{
	this->x = x;
	this->y = y;
	this->bindex = bindex;
	this->id = ++(this->nextID);
}

unsigned int Point::get_id() {
	return this->id;
}

float Point::get_x() {
	return this->x;
}

float Point::get_y() {
	return this->y;
}

unsigned int Point::get_b() {
	return this->bindex;
}

void Point::set_x(float x) {
	this->x = x;
}
void Point::set_y(float y) {
	this->y = y;
}

void Point::set_b(unsigned int bindex) {
	this->bindex = bindex;
}

void Point::update() {
	return;
}