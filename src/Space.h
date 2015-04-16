#ifndef SPACE_H
#define SPACE_H

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdint>
#include <vector>
#include <SDL2/SDL.h>
using namespace std;

class Space
{
	public:
		Space(int screen_w, int screen_h, int fps);
		~Space();

		void CreateDot(int x, int y, int8_t r, int8_t g, int8_t b, pair<float, float> dir, float vel);
		void run();
	private:
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Rect backRect;

		int FPS;
		bool running;
		struct Dot;
		vector<Dot> dots;

		void UpdateDots();
		void DrawDots();
		void DrawBackground();
		void logSDLError(ostream &os, const string &msg);
		void SpaceLoop(int fps);
};

#endif