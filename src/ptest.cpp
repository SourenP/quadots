#include <iostream>
#include "Point.h"
#include "Simulation.h"
#include <stdlib.h>
#include <chrono>
#include <ctime>
using namespace std;

void random_move(Point::Point_p p, Control<Point>& c) {
    vector<Point::Point_p> elements = c.neighbors(p, 50);
    p->set_x(c.random_pos(0,800));
    p->set_y(c.random_pos(0,800));
}

int main()
{   // Brains
    Simulation<Point>::rule move = &random_move;
    Simulation<Point>::behavior pattern = {move};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>();

    // Create behavior circle
    int b = s->CreateBehavior(pattern);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateRandElements(10000, 10, 800, 10, 800, b);

    // Run this only for testing logic (NOT FOR MEASURE)
    //Renderer<Point> twodee = Renderer<Point>(800, 800, 1);
    //s->Run(20, twodee);

    // Run this for measure
    int step = 50;

    // Start timing
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    s->Run(step);
    // End timing
    end = std::chrono::system_clock::now();
    
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    
    std::cout << "finished computation at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << "s\n";

    delete s;
    
    return 0;
}
