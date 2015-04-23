#include "Control.h"
using namespace std;

Control::Control(State *s)
{
	this->state = s;
}

float Control::get_avgY() {
	float sum = 0;
	for(Point::Point_p p : state->points) {
		sum += p->y;
	}
	return sum/state->points.size();
}