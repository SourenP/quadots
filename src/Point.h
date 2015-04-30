#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <memory>
using namespace std;

class Point
{
    protected:
        static int nextID;
        unsigned id;
    public:
        typedef shared_ptr<Point> Point_p;

        Point();
        Point(float x, float y, int bindex);

        int get_id() const;
        float get_x() const;
        float get_y() const;
        int get_b() const;

        void set_x(float x);
        void set_y(float y);
        void set_b(int bindex);

        void update();
    private:
        float x;
        float y;
        int bindex;
};

#endif