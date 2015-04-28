#include <iostream>
#include "Simulation.h"
using namespace std;


void rotate(Point::Point_p d, Control<Point>& c) {
    d->set_x(d->get_x()+1);
    d->set_y(d->get_y()+1);
}


int main()
{
    // Brains
    Simulation<Point>::rule rot = &rotate;
    Simulation<Point>::behavior circle = {rot};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(200, 200, b);
    s->CreateElement(200, 200, b);

    // Initialize Renderer
    Renderer<Point> twodee = Renderer<Point>(400,400, 32);

    // Run Simulation for 200 steps
    s->Run(200, twodee);

    delete s;
    return 0;
}