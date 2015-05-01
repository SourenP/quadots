#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include "Renderer.h"
#include "Control.h"
using namespace std;

// Declaration

template <class elem>
class  Simulation
{
public:
    typedef shared_ptr<elem> Elem_p;
    typedef void (*rule)(Elem_p, Control<elem>&);
    typedef vector<rule> behavior;

    Simulation(double width, double height);
    ~Simulation();

    void CreateElement(elem e);
    int CreateBehavior(behavior &b);
    vector<Elem_p> Run(int gen_count, bool print);
    vector<Elem_p> Run(int gen_count, Renderer<elem> &renderer);

private:
    Control<elem> *control;
    State<elem> *curr_state;
    vector<behavior> behaviors;
    void UpdateState();
    void DrawElements();
    void logError(const string &msg);
    float sim_width;
    float sim_height;
};

// Definition

/*
    Constructor
    Sets wdith and height of the simulation (needed for the state)
    And creates the State and Control objects of the simulation.
*/
template <class elem>
Simulation<elem>::Simulation(double width, double height) {
    this->sim_width = width;
    this->sim_height = height;
    this->curr_state = new State<elem>(width, height);
    this->control = new Control<elem>(curr_state);
}

/*
    Destructor
    Delete state and control.
*/
template <class elem>
Simulation<elem>::~Simulation()
{   
    delete curr_state;
    delete control;
}

/*
    gen_count times (0 is infinite):
    Updates state and if print is true, print the state.
*/
template <class elem>
vector<shared_ptr<elem>> Simulation<elem>::Run(int gen_count, bool print) {
    if (gen_count == 0)
        while (true) {
            UpdateState();
            if (print) cout << *curr_state << endl;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            if (print) cout << *curr_state << endl;
        }
    return curr_state->get_elements();
}

/*
    gen_count time (0 is infinite): 
    Updates state and renders it using renderer passed in.
*/
template <class elem>
vector<shared_ptr<elem>> Simulation<elem>::Run(int gen_count, Renderer<elem> &renderer) {
    bool quit = false;
    // Update and draw
    if (gen_count == 0)
        while (true) {
            UpdateState();
            quit = renderer.RenderState(*curr_state);
            if (quit) return curr_state->get_elements();;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            quit = renderer.RenderState(*curr_state);
            if (quit) return curr_state->get_elements();;
        }
    return curr_state->get_elements();;
}

/*
    Updates the current state by assigning it a new altered state.
*/
template <class elem>
void Simulation<elem>::UpdateState() {
    // Get the elements from the current state
    vector<Elem_p> curr_elements = curr_state->get_elements();
    // Creating a new state
    State<elem> *new_state = new State<elem>(sim_width, sim_height);
    // For each element in current state:
    for (Elem_p p : curr_elements) {
        // Copy the element
        Elem_p new_p(new elem(*p));
        // Check if behavior is valid
        if (new_p->get_b() >= 0) {
            if (new_p->get_b() > behaviors.size()) {
                logError("Behavior index out of range.");
                return;
            } 
            // Apply rules in behavior
            for (rule r : behaviors[new_p->get_b()])
                r(new_p, *control);
        }
        new_p->update();
        new_state->add(new_p);
    }

    // Delete old state and replace with new
    delete curr_state;
    curr_state = new_state;
    control->setState(curr_state);
}

/*
    Creates a new element and returns a shared pointer to it.
*/
template <class elem>
void Simulation<elem>::CreateElement(elem e) {
    Elem_p new_element_p(new elem(e));
    curr_state->add(new_element_p);
}

/*
    Adds the passed behavior to the behaviors container.
    Returns the index it was added to give to an element.
*/
template <class elem>
int Simulation<elem>::CreateBehavior(behavior &b) {
    this->behaviors.push_back(b);
    return (behaviors.size() - 1);
}

/*
    Logs string to cerr with "error: " at the start.
*/
template <class elem>
void Simulation<elem>::logError(const string &msg) {
    cerr << " error: " << msg << endl;
}

#endif