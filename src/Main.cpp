#include <iostream>
#include "Simulation.h"
using namespace std;


void rotate(Point::Point_p p, Control& c) {
    p->ang += 2;
}


int main()
{
    // Brains
    Simulation::rule rot = &rotate;
    Simulation::behavior circle = {rot};

    // Initialize Simulation
    Simulation *s = new Simulation();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreatePoint(200, 200, 0, 1, b);
    s->CreatePoint(200, 200, 180, 2, b);

    // Initialize Renderer
    Renderer twodee = Renderer(400,400, 32);

    // Run Simulation for 200 steps
    s->Run(200, twodee);

    delete s;
    return 0;
}