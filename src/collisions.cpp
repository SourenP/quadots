#include <iostream>
#include "Dot.h"
#include "Simulation.cpp"
#include <cmath>
using namespace std;

int collision_count = 0;

/*
 Returns a random float in the range [min, max)
 */
float random_pos(int min, int max) {
    return(float) (rand() % max + min);
}

/*
 Sets bounds on point
 */
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

/*
 Simulation behavior
 */
void collision_detection(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 10);
    /* Reverse direction of colliding points by 180 degrees */
    for (auto i : neighbors)
        i->set_ang(i->get_ang() + 180);
}

int main()
{
    // Brains
    Simulation<Dot>::rule r4 = &bounds;
    Simulation<Dot>::rule r1 = &collision_detection;
    Simulation<Dot>::behavior cd = {r1, r4};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>(800, 800);

    // Create behavior circle
    int b1 = s->CreateBehavior(cd);

    // Create random Points
    for(int i=0; i < 200; i++)
        s->CreateElement(Dot(random_pos(0,800), random_pos(0,800),random_pos(0,360), 1, b1));
    
    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(800, 800, 100);

    // Run Simulation for 200 steps
    s->Run(1000, twodee);
    
    delete s;
    return 0;
}

