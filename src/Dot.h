#ifndef DOT_H
#define DOT_H

#include "Point.h"
#include <stdio.h>
#include <memory>
using namespace std;

class Dot: public Point
{
    public:
        typedef shared_ptr<Dot> Dot_p;

        Dot(float x, float y, float ang, float vel, unsigned int bindex);

        //float get_x();
        //float get_y();
        float get_ang();
        float get_vel();

        //void set_x(float x);
        //void set_y(float y);
        void set_ang(float ang);
        void set_vel(float vel);

    private:
        //float x;
        //float y;
        float ang;
        float vel;
        //unsigned int bindex;
};

#endif