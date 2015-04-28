#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <vector>
#include <iostream>
#include "Point.h"
#include "State.h"
using namespace std;

template <class elem>
class Control
{
public:
    Control(State<elem> *s);
    float get_avgY();
private:
	State<elem> *state;
};

#endif
