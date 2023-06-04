#include <SDL2/SDL.h>

#include "..\header\graphics.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(640, 480, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "Datchronicles");
}

Graphics::~Graphics()
{
    SDL_DestroyWindow(this->window);
}
