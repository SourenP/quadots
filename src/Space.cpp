#include "Space.h"
using namespace std;

struct Space::Dot {
    int x;
    int y;
    int8_t r;
    int8_t g;
    int8_t b;
    int8_t a;
    pair<float, float> dir;
    float vel;
};

Space::Space(int screen_w, int screen_h, int32_t fps)
{
    // Create Window
    SCREEN_WIDTH = screen_w;
    SCREEN_HEIGHT = screen_h;
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    backRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    if (window == nullptr) {
        logSDLError(cout, "CreateWindow");
        SDL_Quit();
    }
    FPS = fps;
    running = false;
}

void Space::run() {
    if (!running)
        SpaceLoop(FPS);
}

void Space::SpaceLoop(int32_t fps) {
    running = true;
    //Our event structure
    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT){
                quit = true;
            }
        }
        //Render the scene
        SDL_RenderClear(renderer);
        DrawBackground();

        UpdateDots();
        DrawDots();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/fps); // crashes if negative fps
    }
}

void Space::UpdateDots() {
    for (Dot &d : dots) {
        // Get unit direction
        float dir_l = sqrt(d.dir.first*d.dir.first + d.dir.second*d.dir.second);
        float u_dirx = d.dir.first/dir_l;
        float u_diry = d.dir.second/dir_l;

        // Update location based on direction and velocity
        d.x += u_dirx*d.vel;
        d.y += u_diry*d.vel;
    }
}

void Space::DrawDots() {
    for (Dot d : dots) {
        // note: deal with out of bounds x/y later
        SDL_SetRenderDrawColor(renderer, d.r, d.g, d.b, d.a);
        SDL_RenderDrawPoint(renderer, d.x, d.y);
    }
}

void Space::CreateDot(int x, int y, int8_t r, int8_t g, int8_t b, pair<float, float> dir, float vel) {
    Dot new_dot;
    new_dot.x = x;
    new_dot.y = y;
    new_dot.r = r;
    new_dot.g = g;
    new_dot.a = 255;
    new_dot.dir = dir;
    new_dot.vel = vel;
    dots.push_back(new_dot);
}

void Space::DrawBackground() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &backRect);
}

void Space::logSDLError(ostream &os, const string &msg) {
    os << msg << " error: " << SDL_GetError() << endl;
}

Space::~Space()
{
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}