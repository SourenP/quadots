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
#include "Control.h"

using namespace std;

class Simulation
{
public:
    typedef void (*rule)(Point::Point_p, Control&);
    typedef vector<rule> behavior;

    Simulation();
    ~Simulation();

    State curr_state;
    void CreatePoint(float x, float y, float ang, float vel, int b);
    int CreateBehavior(behavior &b);
    void Run(int gen_count);
    void Run(int gen_count, Renderer &r);
    float get_distance(const Point::Point_p a,const Point::Point_p b);

private:
    Control *control;
    vector<behavior> behaviors;
    void UpdateState();
    void Move(Point::Point_p p);
    void DrawPoints();
    void logError(ostream &os, const string &msg);
};

#endif