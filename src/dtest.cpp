#include <iostream>
#include "Dot.h"
#include "Simulation.cpp"
using namespace std;

/*
void tocom(Dot::Dot_p p, Control<Dot>& c) {
    p->set_x(p->get_x() + (c.get_ncom_x(p) - p->get_x()) / 100));
    p->set_y(p->get_y() + (c.get_ncom_y(p) - p->get_y()) / 100));
}

void align(Dot::Dot_p p, Control<Dot>& c) {
    p->set_ang(p->get_ang() + ((c.get_avg_d(p) - p->get_ang()) / 50));
}
*/

void cohesion(Dot::Dot_p p, Control<Dot>& c) {
    p->set_ang(c.dir_towards(p, 200, 0));
    cout << p->get_ang() << endl;
}


void rotate(Dot::Dot_p p, Control<Dot>& c) {
    p->set_ang(p->get_ang() + 2);
}

int main()
{
    // Brains
    //Simulation<Dot>::rule r1 = &cohesion;
    //Simulation<Dot>::rule r2 = &align;
    //Simulation<Dot>::rule r3 = &seperation;
    //Simulation<Dot>::behavior boid = {r1,r2,r3};

    Simulation<Dot>::rule r1 = &rotate;
    Simulation<Dot>::behavior circle = {r1};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>(400, 400);

    // Create behavior circle
    int b1 = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(Dot(200, 200, 0, 1, b1));
    s->CreateElement(Dot(200, 200, 180, 1, b1));

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(400,400, 24);

    // Run Simulation for 200 steps
    s->Run(500, twodee);

    delete s;
    return 0;
}