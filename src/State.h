#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;

class State
{
public:
    State();
    friend ostream& operator<<(ostream &os, const State& s);
    vector<Point::Point_p> points;
private:
};

#endif