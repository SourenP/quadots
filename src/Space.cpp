#include "Space.h"
using namespace std;

Space::Space(int screen_w, int screen_h, int32_t fps)
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
    FPS = fps;
    quit = false;
}

/*
    Updates and redraws dots.
    Returns true if window was closed.
*/
bool Space::Step() {
    if (!quit) {
        while (SDL_PollEvent(&sdl_e)) {
            if (sdl_e.type == SDL_QUIT){
                quit = true;
            }
        }
        //Render the scene
        SDL_RenderClear(renderer);
        DrawBackground();

        // Update and draw
        UpdateDots();
        DrawDots();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS); // crashes if negative fps
    }
    return quit;
}


/*
    Calculates new position of dots.
*/
void Space::UpdateDots() {
    for (Dot_p d : dots) {
        // Get unit direction
        float dir_l = sqrt(d->dir.first*d->dir.first + d->dir.second*d->dir.second);
        d->dir.first = d->dir.first/dir_l;
        d->dir.second = d->dir.second/dir_l;

        // Update location based on direction and velocity
        d->x += d->dir.first  * d->vel;
        d->y += d->dir.second * d->vel;

        //cout << d->type << ": " << d->vel << endl;
    }
}

/*
    Loops over all dots and draws them.
*/
void Space::DrawDots() {
    for (Dot_p d : dots) {
        // note: deal with out of bounds x/y later
        SDL_SetRenderDrawColor(renderer, d->r, d->g, d->b, d->a);
        SDL_RenderDrawPoint(renderer, d->x, d->y);
    }
}

/*
    Creates a new dot and returns a smart pointer to it.
*/
Space::Dot_p Space::CreateDot(float x, float y, int r, int g, int b, pair<float, float> dir, float vel, int type) {
    Dot_p new_dot(new Dot());
    new_dot->x = x;
    new_dot->y = y;
    new_dot->r = r;
    new_dot->g = g;
    new_dot->a = 255;
    new_dot->dir = dir;
    new_dot->vel = vel;
    new_dot->type = type;
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