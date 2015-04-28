#include <iostream>
#include "Simulation.h"
using namespace std;


void rotate(Dot::Dot_p d, Control<Dot>& c) {
    d->set_ang(d->get_ang() + 2);
}


int main()
{
    // Brains
    Simulation<Dot>::rule rot = &rotate;
    Simulation<Dot>::behavior circle = {rot};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(Dot(200, 200, 0, 1, b));
    s->CreateElement(Dot(200, 200, 180, 1, b));

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(400,400, 32);

    // Run Simulation for 200 steps
    s->Run(500, twodee);

    delete s;
    return 0;
}