#include <iostream>
#include "Space.h"
using namespace std;

int main()
{
    Space *s = new Space(400, 400, 12);


    // Colors
    array<int8_t,4> black = {0,0,0,255};
    array<int8_t,4> red = {255,0,0,255};

    // Initialize dots
    auto dot1 = s->CreateDot(200, 200, black, 0+45, 1, 1);
    auto dot2 = s->CreateDot(200, 200, red, 90+45, 1, 2);
    auto dot3 = s->CreateDot(200, 200, black, 180+45, 1, 3);
    auto dot4 = s->CreateDot(200, 200, red, 275+45, 1, 4);

    // Run simulation until window is closed
    bool quit = false;
    float dist;
    float new_vel;
    while (!quit) {

        // Take a step
        quit = s->Step();

        // Dot1 and Dot3 logic
        // Change velocity based on distance
        dist = s->get_distance(dot1, dot4);
        new_vel = dist/30;
        dot1->vel = new_vel;
        dot3->vel = new_vel;

        // Dot2 and Dot4 logic
        // Change angle slightly
        dot2->ang += 2;
        dot4->ang += 2;
    }

    delete s;
    return 0;
}