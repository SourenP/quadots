#include <iostream>
#include "Dot.h"
#include "Simulation.cpp"
#include <cmath>
using namespace std;


void tocom(Dot::Dot_p p, Control<Dot>& c) {
    p->set_x(p->get_x() + (c.get_ncom_x(p) - p->get_x()) / 100));
    p->set_y(p->get_y() + (c.get_ncom_y(p) - p->get_y()) / 100));
}

void align(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 100);

    float avg_dir = c.avg_dir(neighbors);
    p->set_ang(new_dir(p->get_ang(), avg_dir, 10));
}

void cohesion(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 200);

    float steps = 100;
    float avg_x = c.com_x(neighbors);
    float avg_y = c.com_y(neighbors);

    float goal_dir = c.dir_towards(p, avg_x, avg_y);
    float step_ang = delta_dir(p->get_ang(), goal_dir, steps);
    p->add_ang(step_ang);
}

float delta_dir(float curr_dir, float goal_dir, float steps) {
    float delta1 = goal_dir - curr_dir;
    float delta2 = (goal_dir > curr_dir) ? (delta1 - 360) : (delta1 + 360);
    //cout << delta1 << endl;
    if(abs(delta1) < abs(delta2))
        return delta1/steps;
    else
        return delta2/steps;
}

void rotate(Dot::Dot_p p, Control<Dot>& c) {
    cout << p->get_id() << endl;
    cout << p->get_id() << endl;
}

int main()
{
    // Brains
    //Simulation<Dot>::rule r1 = &cohesion;
    //Simulation<Dot>::rule r2 = &align;
    //Simulation<Dot>::rule r3 = &separation;
    Simulation<Dot>::rule r4 = &cohesion;

    Simulation<Dot>::behavior boid = {r4};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>(400, 400);

    // Create behavior circle
    int b1 = s->CreateBehavior(boid);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateElement(Dot(100, 100, 0, 0, -1));
    s->CreateElement(Dot(200, 200, 0, 1, b1));

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(400,400, 50);

    // Run Simulation for 200 steps
    s->Run(0, twodee);

    delete s;
    return 0;
}