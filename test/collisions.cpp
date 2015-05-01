#include <iostream>
#include "Dot.h"
#include "Simulation.h"
#include <cmath>
using namespace std;

/*
 Returns a random float in the range [min, max)
 */
float random_f(int min, int max) {
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
void collision(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 5);
    if (neighbors.size()) {
        p->add_ang(-2*(360-(90-p->get_ang())));
    }
}

int main()
{
    // Initialize Simulation
    Simulation<Dot> *sim = new Simulation<Dot>(800, 800);

    // Define rules of collisions
    Simulation<Dot>::rule r1 = &collision;
    Simulation<Dot>::rule r2 = &bounds;

    // Put all rules into a behavior
    Simulation<Dot>::behavior col = {r1, r2};

    // Create behavior col
    int b = sim->CreateBehavior(col);

    // Create 200 Dots in random position, random directions, velocity 1, behavior index b (col)
    int count = 200;
    for(int i=0; i < count; i++)
        sim->CreateElement(Dot(random_f(0,800), random_f(0,800), random_f(0,360), 1, b));
    
    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(800, 800, 100);

    // Run Simulation infinitely with renderer
    sim->Run(0, twodee);
    
    delete sim;
    return 0;
}

