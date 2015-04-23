#ifndef SPACE_H
#define SPACE_H
#define PI 3.14159265

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <memory>
#include <SDL2/SDL.h>
using namespace std;

class Dot;
class Space
{
    public:
        typedef shared_ptr<Dot> Dot_p;
        typedef vector<Dot_p> target;
        typedef void (*action)(Dot_p);

        Space(int screen_w, int screen_h, int sps);
        ~Space();

        Dot_p CreateDot(float x, float y, array<int8_t,4> color, float ang, float vel, int type);
        void Run(vector<pair<target, action>> tas);
        float get_distance(const Dot_p a,const Dot_p b);

    private:
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Rect backRect;

        int SPS;
        bool quit;
        SDL_Event sdl_e;

        vector<Dot_p> dots;

        void UpdateDots();
        void DrawDots();
        void DrawBackground();
        void logSDLError(ostream &os, const string &msg);
};

#endif