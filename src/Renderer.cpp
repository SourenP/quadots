#include "Renderer.h"
using namespace std;

Renderer::Renderer(int screen_w, int screen_h, int32_t sps)
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
    Loops over all points and draws them.
*/
bool Renderer::RenderState(State &s) {
    while (SDL_PollEvent(&sdl_e)) {
        if (sdl_e.type == SDL_QUIT){
            return true;
        }
    }

    // Render the scene
    SDL_RenderClear(renderer);
    DrawBackground();

    // Draw points
    for (Point::Point_p p : s.points) {
        // note: deal with out of bounds x/y later
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        
        SDL_RenderDrawPoint(renderer, p->x-1, p->y);
        SDL_RenderDrawPoint(renderer, p->x, p->y-1);
        SDL_RenderDrawPoint(renderer, p->x-1, p->y-1);
        SDL_RenderDrawPoint(renderer, p->x+1, p->y);
        SDL_RenderDrawPoint(renderer, p->x, p->y+1);
        SDL_RenderDrawPoint(renderer, p->x+1, p->y+1);
        SDL_RenderDrawPoint(renderer, p->x+1, p->y-1);
        SDL_RenderDrawPoint(renderer, p->x-1, p->y+1);
        SDL_RenderDrawPoint(renderer, p->x, p->y);
    }

    // Cleanup
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/SPS); // crashes if negative sps

    return false;
}

/*
    Draws a white background using a rectangle.
*/
void Renderer::DrawBackground() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &backRect);
}

void Renderer::logSDLError(ostream &os, const string &msg) {
    os << msg << " error: " << SDL_GetError() << endl;
}

Renderer::~Renderer()
{
    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}