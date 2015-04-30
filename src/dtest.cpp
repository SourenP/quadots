#include <iostream>
#include "Point.h"
#include "Dot.h"
#include "Simulation.h"
#include <cmath>
using namespace std;

float delta_dir(float curr_dir, float goal_dir, float steps) {
    float delta1 = goal_dir - curr_dir;
    float delta2 = (goal_dir > curr_dir) ? (delta1 - 360) : (delta1 + 360);
    if(abs(delta1) < abs(delta2))
        return delta1/steps;
    else
        return delta2/steps;
}

void separation(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 50);
    float steps = 10;

    if(neighbors.size()) {
        float avg_x = c.avg_x(neighbors);
        float avg_y = c.avg_y(neighbors);
        float goal_dir = c.dir_towards(p, avg_x, avg_y) - 180;
        float step_ang = delta_dir(p->get_ang(), goal_dir, steps);
        p->add_ang(step_ang);
    }
}

void alignment(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 100);
    float steps = 10;

    if(neighbors.size()) {
        float avg_dir = c.avg_dir(neighbors);
        float step_ang = delta_dir(p->get_ang(), avg_dir, steps);
        p->add_ang(step_ang);
    }
}

void cohesion(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 150);
    float steps = 10;

    if(neighbors.size()) {
        float avg_x = c.avg_x(neighbors);
        float avg_y = c.avg_y(neighbors);
        float goal_dir = c.dir_towards(p, avg_x, avg_y);
        float step_ang = delta_dir(p->get_ang(), goal_dir, steps);
        p->add_ang(step_ang);
    }
}

void bounds(Dot::Dot_p p, Control<Dot>& c) {
    if(p->get_x() <= 0)
        p->set_x(799);
    else if(p->get_x() >= 800)
        p->set_x(1);
    if(p->get_y() <= 0)
        p->set_y(799);
    else if(p->get_y() >= 800)
        p->set_y(1);
}

int main()
{
    // Brains
    Simulation<Dot>::rule r1 = &cohesion;
    Simulation<Dot>::rule r2 = &alignment;
    Simulation<Dot>::rule r3 = &separation;
    Simulation<Dot>::rule r4 = &bounds;

    Simulation<Dot>::behavior boid = {r1,r2,r3,r4};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>(800, 800);

    // Create behavior circle
    int b1 = s->CreateBehavior(boid);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateRandDots(100, 10, 790, 10, 790, b1);

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(800, 800, 100);

    // Run Simulation for 1000 steps
    s->Run(5000, twodee);

    delete s;
    return 0;
}