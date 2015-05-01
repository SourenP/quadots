#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include "Dot.h"
#include "Simulation.h"
using namespace std;

// Helper functions

/*
    Returns a random float in the range [min, max) 
*/
float random_f(int min, int max) {
    return(float) (rand() % max + min);
}

/*
    Returns value of direction to add "steps" times to curr_dir for it to equal goal_dir
*/
float delta_dir(float curr_dir, float goal_dir, float steps) {
    float delta1 = goal_dir - curr_dir;
    float delta2 = (goal_dir > curr_dir) ? (delta1 - 360) : (delta1 + 360);
    if(abs(delta1) < abs(delta2))
        return delta1/steps;
    else
        return delta2/steps;
}

// Boid rules

/*
    Steer to avoid crowding local flockmates
*/
void separation(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 50);
    float steps = 15;

    if(neighbors.size()) {
        float avg_x = c.avg_x(neighbors);
        float avg_y = c.avg_y(neighbors);
        float goal_dir = c.dir_towards(p, avg_x, avg_y) - 180;
        float step_ang = delta_dir(p->get_ang(), goal_dir, steps);
        p->add_ang(step_ang);
    }
}

/*
    Steer towards the average heading of local flockmates
*/
void alignment(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 100);
    float steps = 10;

    if(neighbors.size()) {
        float avg_dir = c.avg_dir(neighbors);
        float step_ang = delta_dir(p->get_ang(), avg_dir, steps);
        p->add_ang(step_ang);
    }
}

/*
    Steer to move toward the average position of local flockmates
*/
void cohesion(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 150);
    float steps = 15;

    if(neighbors.size()) {
        float avg_x = c.avg_x(neighbors);
        float avg_y = c.avg_y(neighbors);
        float goal_dir = c.dir_towards(p, avg_x, avg_y);
        float step_ang = delta_dir(p->get_ang(), goal_dir, steps);
        p->add_ang(step_ang);
    }
}

/*
    Loop dots to other side if they go out of bounds
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

int main()
{
    // Initialize Simulation 800x800 pixels
    Simulation<Dot> *sim = new Simulation<Dot>(800, 800);

    // Define rules of boids
    Simulation<Dot>::rule r1 = &cohesion;
    Simulation<Dot>::rule r2 = &alignment;
    Simulation<Dot>::rule r3 = &separation;
    Simulation<Dot>::rule r4 = &bounds;

    // Put all rules into a behavior
    Simulation<Dot>::behavior boid = {r1, r2, r3, r4};

    // Create behavior boid
    int b = sim->CreateBehavior(boid);

    // Define random seed
    srand(time(NULL));

    // Create 200 Dots in random position, random directions, velocity 1, behavior index b (boids)
    int count = 200;
    for(int i=0; i < count; i++)
        sim->CreateElement(Dot(random_f(0,800), random_f(0,800), random_f(0,360), 1, b));

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(800, 800, 200);

    // Run Simulation infinitely with renderer
    sim->Run(0, twodee);

    delete sim;
    return 0;
}