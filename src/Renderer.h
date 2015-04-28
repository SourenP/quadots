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
	Renderer(int screen_w, int screen_h, int sps);
	~Renderer();

	bool RenderState(State<elem> &s);
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect backRect;

    int SPS;
    bool quit;
    SDL_Event sdl_e;

    void DrawBackground();
    void logSDLError(ostream &os, const string &msg);
};

#endif