#include <iostream>
#include "Simulation.h"
using namespace std;

void rule1(Point::Point_p p, Control<Point>& c) {
    p->set_x(p->get_x()+1);
}

int main()
{

    // Brains
    Simulation<Point>::rule rot = &rule1;
    Simulation<Point>::behavior circle = {rot};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>(400,400);

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(Point(100, 100, b));
    s->CreateElement(Point(300, 300, b));

    // Initialize Renderer
    Renderer<Point> twodee = Renderer<Point>(400, 400, 50);

    // Run Simulation for 200 steps
    s->Run(200, twodee);

    delete s;
    return 0;
}