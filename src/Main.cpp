#include <iostream>
#include "Space.h"
#include "Dot.h"
using namespace std;

void rotate(Space::Dot_p d) {
    d->ang += 2;
}

int main()
{
    // Initialize space
    Space *s = new Space(400, 400, 32);

    // Create black r = 0, g = 0, b = 0, a = 255
    array<int8_t,4> black = {0, 0, 0, 255};

    // Create two dots in the middle of the screen facing opposite directions
    auto dot1 = s->CreateDot(200, 200, black, 0, 1, 1);
    auto dot2 = s->CreateDot(200, 200, black, 180, 1, 1);

    // Create target and action
    Space::target dots = {dot1, dot2};
    Space::action rot = &rotate;

    // Run the simulation
    s->Run({make_pair(dots, rot)});

    delete s;
    return 0;
}