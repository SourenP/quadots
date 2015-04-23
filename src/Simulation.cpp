#include "Simulation.h"
using namespace std;

Simulation::Simulation() {
    control = new Control(&curr_state);
}

/*
    Updates and prints Points @gen_count times.
*/
void Simulation::Run(int gen_count) {
    // Update and print
    if (gen_count == 0)
        while (true) {
            UpdateState();
            cout << curr_state << endl;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            cout << curr_state << endl;
        }
}

/*
    Updates and renders Points @gen_count times.
*/
void Simulation::Run(int gen_count, Renderer &r) {
    bool quit = false;
    // Update and draw
    if (gen_count == 0)
        while (true) {
            UpdateState();
            quit = r.RenderState(curr_state);
            if (quit) return;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            quit = r.RenderState(curr_state);
            if (quit) return;
        }
}

/*
    Calculates new position of Points.
*/
void Simulation::UpdateState() {
    for (Point::Point_p p : curr_state.points) {
        for (rule r : behaviors[p->bindex])
            r(p, *control);
        Move(p);
    }
}

void Simulation::Move(Point::Point_p p) {
    // Update location based on angle and velocity
    p->x += cos(p->ang * PI/180.0) * p->vel;
    p->y += sin(p->ang * PI/180.0) * p->vel;
}

/*
    Creates a new Point and returns a smart pointer to it.
*/
void Simulation::CreatePoint(float x, float y, float ang, float vel, int b) {
    Point::Point_p new_point(new Point(x, y, ang, vel, b));
    curr_state.points.push_back(new_point);
}

int Simulation::CreateBehavior(behavior &b) {
    this->behaviors.push_back(b);
    return (behaviors.size() - 1);
}

float Simulation::get_distance(const Point::Point_p a, const Point::Point_p b) {
    return sqrt(pow(a->x - b->x,2) + pow(a->y - b->y,2));
}

Simulation::~Simulation()
{
    delete control;
}
