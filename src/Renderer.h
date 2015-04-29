#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <SDL2/SDL.h>
#include "State.h"
using namespace std;

template <class elem>
class Renderer
{
public:
	Renderer(int screen_w, int screen_h, float sps);
	~Renderer();

	bool RenderState(State<elem> &s);
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect backRect;

    float SPS;
    bool quit;
    SDL_Event sdl_e;

    void DrawBackground();
    void logSDLError(ostream &os, const string &msg);
};

#endif

template <class elem>
Renderer<elem>::Renderer(int screen_w, int screen_h, float sps)
{
    // Create SDL Window
    SCREEN_WIDTH = screen_w;
    SCREEN_HEIGHT = screen_h;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

    // Set background to white.
    backRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    // Check if window initialized.
    if (window == nullptr) {
        logSDLError(cout, "CreateWindow");
        SDL_Quit();
    }

    // Initialize variables.
    SPS = sps;
    quit = false;
}

/*
    Loops over all elements and draws them.
*/
template <class elem>
bool Renderer<elem>::RenderState(State<elem> &s) {
    while (SDL_PollEvent(&sdl_e)) {
        if (sdl_e.type == SDL_QUIT){
            return true;
        }
    }

    // Render the scene
    SDL_RenderClear(renderer);
    DrawBackground();

    // Draw elements
    vector<shared_ptr<elem>> elements = s.get_elements();
    for (auto p : elements) {
        // note: deal with out of bounds x/y later
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderDrawPoint(renderer, p->get_x()-1, p->get_y());
        SDL_RenderDrawPoint(renderer, p->get_x(), p->get_y()-1);
        SDL_RenderDrawPoint(renderer, p->get_x()-1, p->get_y()-1);
        SDL_RenderDrawPoint(renderer, p->get_x()+1, p->get_y());
        SDL_RenderDrawPoint(renderer, p->get_x(), p->get_y()+1);
        SDL_RenderDrawPoint(renderer, p->get_x()+1, p->get_y()+1);
        SDL_RenderDrawPoint(renderer, p->get_x()+1, p->get_y()-1);
        SDL_RenderDrawPoint(renderer, p->get_x()-1, p->get_y()+1);
        SDL_RenderDrawPoint(renderer, p->get_x(), p->get_y());
    }

    // Cleanup
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/SPS); // crashes if negative sps

    return false;
}

/*
    Draws a white background using a rectangle.
*/
template <class elem>
void Renderer<elem>::DrawBackground() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &backRect);
}

template <class elem>
void Renderer<elem>::logSDLError(ostream &os, const string &msg) {
    os << msg << " error: " << SDL_GetError() << endl;
}

template <class elem>
Renderer<elem>::~Renderer()
{
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}