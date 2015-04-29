#include <iostream>
#include "Point.h"
#include "Simulation.cpp"
using namespace std;

void rule1(Point::Point_p p, Control<Point>& c) {
    vector<Point::Point_p> elements = c.qneighbors(p, 400);
    p->set_x(elements[0]->get_x());
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
    //Renderer<Point> twodee = Renderer<Point>(400, 400, 1);

    // Run Simulation for 200 steps
    s->Run(200);

    delete s;
    return 0;
}