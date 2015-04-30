#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <memory>
using namespace std;

class Point
{
    protected:
        static int nextID;
    public:
        typedef shared_ptr<Point> Point_p;

        Point();
        Point(float x, float y, unsigned int bindex);

        unsigned int get_id();
        float get_x();
        float get_y();
        unsigned int get_b();

        void set_x(float x);
        void set_y(float y);
        void set_b(unsigned int bindex);

        void update();
    private:
        float x;
        float y;
        unsigned int bindex;
        unsigned id;
};

#endif