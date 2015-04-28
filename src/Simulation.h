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
#include "Dot.h"

using namespace std;

template <class elem>
class  Simulation
{
public:
    typedef shared_ptr<elem> Elem_p;
    typedef void (*rule)(Elem_p, Control<elem>&);
    typedef vector<rule> behavior;

    Simulation();
    ~Simulation();

    State<elem> curr_state;
    void CreateElement(float x, float y, int b);
    int CreateBehavior(behavior &b);
    void Run(int gen_count);
    void Run(int gen_count, Renderer<elem> &r);
    float get_distance(const Elem_p a,const Elem_p b);

private:
    Control<elem> *control;
    vector<behavior> behaviors;
    void UpdateState();
    void DrawElements();
    void logError(ostream &os, const string &msg);
};

#endif

