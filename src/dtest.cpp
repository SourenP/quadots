#include <iostream>
#include "Simulation.h"
using namespace std;

/*
void tocom(Dot::Dot_p p, Control<Dot>& c) {
    p->set_x(p->get_x() + (c.get_ncom_x(p) - p->get_x()) / 100));
    p->set_y(p->get_y() + (c.get_ncom_y(p) - p->get_y()) / 100));
}
*/

void align(Dot::Dot_p p, Control<Dot>& c) {
    p->set_ang(p->get_ang() + ((c.get_avg_d(p) - p->get_ang()) / 50));
}

void cohesion(Dot::Dot_p p, Control<Dot>& c) {
    p->set_ang(c.dir_towards(100, 100));
}

int main()
{
    // Brains
    Simulation<Dot>::rule r1 = &cohesion;
    Simulation<Dot>::behavior circle = {r1};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    //s->CreateElement(Dot(100, 100, 90, 1, b));
    s->CreateElement(Dot(300, 300, 180, 1, b));

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(400,400, 24);

    // Run Simulation for 200 steps
    s->Run(500, twodee);

    delete s;
    return 0;
}