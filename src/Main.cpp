#include <iostream>
#include "Space.h"
using namespace std;

int main()
{
    Space *s = new Space(400, 400, 12);

    // Initialize dots
    auto dot1 = s->CreateDot(200, 200, 0, 0, 0, make_pair(1,1), 1, 1);
    auto dot2 = s->CreateDot(200, 200, 0, 0, 0, make_pair(1,-1), 1, 2);
    auto dot3 = s->CreateDot(200, 200, 0, 0, 0, make_pair(-1,1), 1, 3);
    auto dot4 = s->CreateDot(200, 200, 0, 0, 0, make_pair(-1,-1), 1, 4);

    // Run simulation until window is closed
    bool quit = false;
    float dist;
    float new_vel;
    while (!quit) {

        // Take a step
        quit = s->Step();

        // Change velocity based on distance
        dist = s->get_distance(dot1, dot4);
        new_vel = dist/30;
        dot1->vel = new_vel;
        dot4->vel = new_vel;
    }

    delete s;
    return 0;
}