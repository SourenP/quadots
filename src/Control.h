#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Point.h"
#include "State.h"
using namespace std;

class Control
{
public:
    Control(State *s);
    float get_avgY();
private:
	State *state;
};

#endif
