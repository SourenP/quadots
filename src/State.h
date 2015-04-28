#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

template <class elem> class State
{
public:
    State();
    //friend ostream& operator<<(ostream &os, const State<elem>& s);
    vector<shared_ptr<elem>> elements;
private:
};

#endif