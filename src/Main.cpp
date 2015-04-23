#include <iostream>
#include "Simulation.h"
using namespace std;

int main()
{
    // Initialize Renderer
    Renderer twodee = Renderer(400,400, 24);

    // Initialize Simulation
    Simulation *s = new Simulation();

    // Create two Points in the middle of the screen facing opposite directions
    auto Point1 = s->CreatePoint(200, 200, 0, 1);
    auto Point2 = s->CreatePoint(200, 200, 180, 1);

    s->Run(100, twodee);

    delete s;
    return 0;
}