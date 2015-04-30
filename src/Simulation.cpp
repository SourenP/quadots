#ifndef Simulation_H
#define Simulation_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cstdint>
#include <SDL2/SDL.h>
#include <cstddef>
#include "Quadtree.cpp"
#include "State.cpp"
#include "Renderer.cpp"
#include "Control.cpp"

using namespace std;

template <class elem>
class  Simulation
{
public:
    typedef shared_ptr<elem> Elem_p;
    typedef void (*rule)(Elem_p, Control<elem>&);
    typedef vector<rule> behavior;

    Simulation(double width, double height);
    ~Simulation();

    State<elem> *curr_state;
    void CreateElement(elem e);
    void CreateRandElements(int count, int min_x, int max_x, int min_y, int max_y, int bindex);
    int CreateBehavior(behavior &b);
    void Run(int gen_count);
    void Run(int gen_count, Renderer<elem> &r);

private:
    Control<elem> *control;
    vector<behavior> behaviors;
    void UpdateState();
    void DrawElements();
    void logError(ostream &os, const string &msg);
    float sim_width;
    float sim_height;
};

// CPP

template <class elem>
Simulation<elem>::Simulation(double width, double height) {
    this->sim_width = width;
    this->sim_height = height;
    this->curr_state = new State<elem>(width, height);
    this->control = new Control<elem>(curr_state);
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
            //cout << *curr_state << endl;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            //cout << *curr_state << endl;
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
            quit = r.RenderState(*curr_state);
            if (quit) return;
        }
    else
        for(int i=0; i < gen_count; i++) {
            UpdateState();
            quit = r.RenderState(*curr_state);
            if (quit) return;
        }
}

/*
    Calculates new position of Elements.
*/
template <class elem>
void Simulation<elem>::UpdateState() {
    vector<Elem_p> curr_elements = curr_state->get_elements();
    State<elem> *new_state = new State<elem>(sim_width, sim_height);
    for (Elem_p p : curr_elements) {
        Elem_p new_p(new elem(*p));
        if (new_p->get_b() >= 0) {
            if (new_p->get_b() > behaviors.size()) {
                logError(cerr, "Behavior index out of range.");
                return;
            } 
                for (rule r : behaviors[new_p->get_b()])
                    r(new_p, *control);
        }
        new_p->update();
        new_state->add(new_p);
    }
    delete curr_state;
    curr_state = new_state;
    control->setState(curr_state);
}

/*
    Creates a new Element and returns a smart pointer to it.
*/
template <class elem>
void Simulation<elem>::CreateElement(elem e) {
    Elem_p new_element_p(new elem(e));
    curr_state->add(new_element_p);
}

template <class elem>
void Simulation<elem>::CreateRandElements(int count, int min_x, int max_x, int min_y, int max_y, int bindex) {
    srand(time(NULL));
    for(int i=0; i < count; i++) {
        float x = (float) (rand() % max_x + min_x);
        float y = (float) (rand() % max_y + min_y);
        Elem_p new_element_p(new elem(x,y,bindex));
        curr_state->add(new_element_p);
    }
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
    delete curr_state;
    delete control;
}

#endif