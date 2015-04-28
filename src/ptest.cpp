#include <iostream>
#include "Simulation.h"
using namespace std;


void rotate(Point::Point_p p, Control<Point>& c) {
    Point::Point_p n = c.get_nearest(p);
    if (n != nullptr) {
        p->set_x(p->get_x() - (p->get_x() - n->get_x())/10);
        p->set_y(p->get_y() - (p->get_y() - n->get_y())/10);
    } else {
        cout << "null?" << endl;
    }
}

int main()
{
    // Brains
    Simulation<Point>::rule rot = &rotate;
    Simulation<Point>::behavior circle = {rot};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>();

    // Create behavior circle
    int b = s->CreateBehavior(circle);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(Point(100, 100, b));
    s->CreateElement(Point(200, 200, b));
    s->CreateElement(Point(300, 300, b));

    // Initialize Renderer
    Renderer<Point> twodee = Renderer<Point>(400, 400, 12);

    // Run Simulation for 200 steps
    s->Run(200, twodee);

    delete s;
    return 0;
}