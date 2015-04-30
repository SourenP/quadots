#include <iostream>
#include "Point.h"
#include "Simulation.cpp"
#include <stdlib.h>
#include <time.h>
using namespace std;

void random_move(Point::Point_p p, Control<Point>& c) {
    vector<Point::Point_p> elements = c.qneighbors(p, 400);
    srand(time(NULL));
    int delta = rand() % 2;

    int move = (int) elements.size();
    float new_posx, new_posy;
    
    if (delta == 1) {
        new_posx = p->get_x() + move*(rand() % 10 + 5);
        new_posy = p->get_y() - move*(rand() % 10 + 5);
        
        if (new_posx > 800 || new_posx < 0)
            //new_posx = (float) (rand() % 800 + 1);
            new_posx = 400;
        
        if (new_posy > 800 || new_posy < 0)
            //new_posy = (float) (rand() % 800 + 1);
            new_posy = 400;

        p->set_x(new_posx);
        p->set_y(new_posy);
        
    }
    else {
        new_posx = p->get_x() + move*(rand() % 10 + 5);
        new_posy = p->get_y() - move*(rand() % 10 + 5);
        
        if (new_posx > 800 || new_posx < 0)
            new_posx = (float) (rand() % 800 + 1);
        
        if (new_posy > 800 || new_posy < 0)
            new_posy = (float) (rand() % 800 + 1);
        
        p->set_x(p->get_x() - move);
        p->set_y(p->get_y() + move);
    }
}

int main()
{

    // Brains
    Simulation<Point>::rule move = &random_move;
    Simulation<Point>::behavior pattern = {move};

    // Initialize Simulation
    Simulation<Point> *s = new Simulation<Point>(800, 800);

    // Create behavior circle
    int b = s->CreateBehavior(pattern);

    // Create two Points in the middle of the screen facing opposite directions
    s->CreateRandElements(10, 10, 800, 10, 800, b);

    // Initialize Renderer
    Renderer<Point> twodee = Renderer<Point>(800, 800, 1);

    // Run Simulation for 200 steps
    s->Run(20, twodee);

    delete s;
    return 0;
}
