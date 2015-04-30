#include <iostream>
#include "Dot.h"
#include "Simulation.cpp"
#include <cmath>
using namespace std;

int collision_count = 0;
float delta_dir(float curr_dir, float goal_dir, float steps) {
    float delta1 = goal_dir - curr_dir;
    float delta2 = (goal_dir > curr_dir) ? (delta1 - 360) : (delta1 + 360);
    //cout << delta1 << endl;
    if(abs(delta1) < abs(delta2))
        return delta1/steps;
    else
        return delta2/steps;
}

void separation(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 50);
    float steps = 10;

    if(neighbors.size()) {
        float avg_x = c.com_x(neighbors);
        float avg_y = c.com_y(neighbors);
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
        float avg_x = c.com_x(neighbors);
        float avg_y = c.com_y(neighbors);
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

void collision_detection(Dot::Dot_p p, Control<Dot>& c) {
    vector<Dot::Dot_p> neighbors = c.qneighbors(p, 5);
    collision_count += neighbors.size();
    
    p->set_ang(360 - p->get_ang());
}

int main()
{
    // Brains
    /*Simulation<Dot>::rule r1 = &cohesion;
    Simulation<Dot>::rule r2 = &alignment;
    Simulation<Dot>::rule r3 = &separation;
    Simulation<Dot>::rule r4 = &bounds;*/

    Simulation<Dot>::rule r1 = &collision_detection;
    Simulation<Dot>::behavior cd = {r1};

    // Initialize Simulation
    Simulation<Dot> *s = new Simulation<Dot>(800, 800);

    // Create behavior circle
    int b1 = s->CreateBehavior(cd);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateRandDots(500, 10, 790, 10, 790, b1);

    // Initialize Renderer
    Renderer<Dot> twodee = Renderer<Dot>(800, 800, 100);

    // Run Simulation for 200 steps
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    s->Run(1000, twodee);

    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    std::cout << "finished computation at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << "s\n";
    
    cout << collision_count/elapsed_seconds.count();
    delete s;
    return 0;
}