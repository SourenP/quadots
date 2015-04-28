#ifndef Simulation_H
#define Simulation_H

#include <stdio.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include "Point.h"
#include "State.h"
#include "Renderer.h"
#include "Control.h"
#include "Dot.h"

using namespace std;

template <class elem>
class  Simulation
{
public:
    typedef shared_ptr<elem> Elem_p;
    typedef void (*rule)(Elem_p, Control<elem>&);
    typedef vector<rule> behavior;

    Simulation();
    ~Simulation();

    State<elem> curr_state;
    void CreateElement(elem e);
    int CreateBehavior(behavior &b);
    void Run(int gen_count);
    void Run(int gen_count, Renderer<elem> &r);

private:
    Control<elem> *control;
    vector<behavior> behaviors;
    void UpdateState();
    void DrawElements();
    void logError(ostream &os, const string &msg);
};

// CPP

template <class elem>
Simulation<elem>::Simulation() {
    control = new Control<elem>(&curr_state);
}

/*
    Updates and prints Elements @gen_count times.
*/
template <class elem>
void Simulation<elem>::Run(int gen_count) {
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
    Updates and renders Elements @gen_count times.
*/
template <class elem>
void Simulation<elem>::Run(int gen_count, Renderer<elem> &r) {
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
    Calculates new position of Elements.
*/
template <class elem>
void Simulation<elem>::UpdateState() {
    State<elem> new_state = curr_state;
    for (Elem_p p : new_state.elements) {
        if (p->get_b() > behaviors.size()) {
            logError(cerr, "Behavior index out of range.");
            return;
        }
        for (rule r : behaviors[p->get_b()])
            r(p, *control);
        p->update();
    }
    curr_state = new_state;
}

/*
    Creates a new Element and returns a smart pointer to it.
*/
template <class elem>
void Simulation<elem>::CreateElement(elem e) {
    Elem_p new_element_p(new elem(e));
    curr_state.elements.push_back(new_element_p);
}

template <class elem>
int Simulation<elem>::CreateBehavior(behavior &b) {
    this->behaviors.push_back(b);
    return (behaviors.size() - 1);
}

template <class elem>
void Simulation<elem>::logError(ostream &os, const string &msg) {
    os << " error: " << msg << endl;
}

template <class elem>
Simulation<elem>::~Simulation()
{
    delete control;
}

#endif