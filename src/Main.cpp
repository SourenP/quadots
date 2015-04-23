#include <iostream>
#include "Simulation.h"
using namespace std;


void rotate(Point::Point_p p, Control& c) {
    p->ang += 2;
    cout << c.get_avgY() << endl;
}


int main()
{
    // Initialize Renderer
    //Renderer twodee = Renderer(400,400, 32);

    // Brains
    Simulation::rule rot = &rotate;
    Simulation::behavior dance = {rot};

    // Initialize Simulation
    Simulation *s = new Simulation();

    // Create behavior dance
    int b = s->CreateBehavior(dance);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreatePoint(200, 200, 0, 1, b);
    s->CreatePoint(200, 200, 180, 2, b);

    s->Run(100);

    delete s;
    return 0;
}