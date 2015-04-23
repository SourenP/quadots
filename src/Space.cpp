#include "Space.h"
#include "Dot.h"
using namespace std;

Space::Space(int screen_w, int screen_h, int32_t sps)
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
    Updates and redraws dots.
    Returns true if window was closed.
*/
void Space::Run(vector<pair<target, action>> tas) {
    while (!quit) {
        while (SDL_PollEvent(&sdl_e)) {
            if (sdl_e.type == SDL_QUIT){
                quit = true;
            }
        }
        //Render the scene
        SDL_RenderClear(renderer);
        DrawBackground();

        // Call actions on targets
        for (pair<target, action> ta : tas)
            for (Dot_p d : ta.first)
                ta.second(d);

        // Update and draw
        UpdateDots();
        DrawDots();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/SPS); // crashes if negative sps
    }
}


/*
    Calculates new position of dots.
*/
void Space::UpdateDots() {
    for (Dot_p d : dots) {
        // Update location based on angle and velocity
        d->x += cos(d->ang * PI/180.0) * d->vel;
        d->y += sin(d->ang * PI/180.0) * d->vel;
    }
}

/*
    Loops over all dots and draws them.
*/
void Space::DrawDots() {
    for (Dot_p d : dots) {
        // note: deal with out of bounds x/y later
        SDL_SetRenderDrawColor(renderer, d->color[0], d->color[1], d->color[2], d->color[3]);
        SDL_RenderDrawPoint(renderer, d->x, d->y);
    }
}

/*
    Creates a new dot and returns a smart pointer to it.
*/
Space::Dot_p Space::CreateDot(float x, float y, array<int8_t,4> color, float ang, float vel, int type) {
    Dot_p new_dot(new Dot(x, y, color, ang, vel, type, this));
    dots.push_back(new_dot);
    return dots.back();
}

float Space::get_distance(const Dot_p a,const Dot_p b) {
    return sqrt(pow(a->x - b->x,2) + pow(a->y - b->y,2));
}

/*
    Draws a white background using a rectangle.
*/
void Space::DrawBackground() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &backRect);
}

void Space::logSDLError(ostream &os, const string &msg) {
    os << msg << " error: " << SDL_GetError() << endl;
}

Space::~Space()
{
    // Destroy dots vector
    // do I do vector.clear();

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}