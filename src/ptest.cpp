#include <iostream>
#include "Point.h"
#include "Simulation.cpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

void random_move(Point::Point_p p, Control<Point>& c) {
    vector<Point::Point_p> elements = c.neighbors(p, 50);
    p->set_x(c.random_pos(0,800));
    p->set_y(c.random_pos(0,800));
}

int main()
{

    // Brains
    Simulation<Point>::rule move = &random_move;
    Simulation<Point>::behavior pattern = {move};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>(800, 800);

    // Create behavior circle
    int b = s->CreateBehavior(pattern);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateRandElements(100, 10, 800, 10, 800, b);

    // Run this only for testing logic (NOT FOR MEASURE)
    Renderer<Point> twodee = Renderer<Point>(800, 800, 1);
    s->Run(20, twodee);

    // Run this for measure
    //int step = 100;
    // Start timing
    //s->Run(step);
    // End timing

    delete s;
    return 0;
}
