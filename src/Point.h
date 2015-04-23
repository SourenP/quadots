#ifndef Point_H
#define Point_H

#include <stdio.h>
#include <memory>
using namespace std;

class Point
{
    public:
    	typedef shared_ptr<Point> Point_p;

        Point(float x, float y, float ang, float vel, int bindex);

        float x;
        float y;
        float ang;
        float vel;
        int bindex;
    private:
};

#endif