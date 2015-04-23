#ifndef DOT_H
#define DOT_H

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
using namespace std;

class Space;
class Dot
{
    public:
        Dot(float x, float y, array<int8_t,4> color, float ang, float vel, int type, Space *s);

        float x;
        float y;
        array<int8_t,4> color;
        float ang;
        float vel;
        int type;
        Space* s; // is space being freed twice because of this?
        
    private:
};

#endif