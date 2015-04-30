#include <iostream>
#include "Point.h"
#include "Simulation.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

void random_move(Point::Point_p p, Control<Point>& c) {
    vector<Point::Point_p> elements = c.qneighbors(p, 50);
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
    s->CreateElement(Point(100, 100, b));
    s->CreateElement(Point(100, 300, b));

    // Run simulation
    Renderer<Point> twodee = Renderer<Point>(800, 800, 1);
    s->Run(1000, twodee);

    delete s;
    return 0;
}
