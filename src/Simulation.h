#ifndef Simulation_H
#define Simulation_H
#define PI 3.14159265

#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include "Point.h"
#include "State.h"
#include "Renderer.h"

using namespace std;

class Simulation
{
public:
    //typedef vector<Point_p> target;
    //typedef void (*action)(Point_p);

    Simulation();
    ~Simulation();

    State curr_state;
    void CreatePoint(float x, float y, float ang, float vel);
    void Run(int gen_count);
    void Run(int gen_count, Renderer &r);
    float get_distance(const Point::Point_p a,const Point::Point_p b);

private:
    void UpdateState();
    void DrawPoints();
};

#endif