#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

SDL_Surface* Graphics::loadImage(const std::string& filePath)
{
    if (spriteSheet.count(filePath) == 0)
    {
        SDL_Surface* ourImage = IMG_Load(filePath.c_str());
        if (!ourImage) std::cout << "[ERROR] IMG_Load: " <<  IMG_GetError() << '\n';
        spriteSheet[filePath] = IMG_Load(filePath.c_str());
    }
    return spriteSheet[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
    SDL_RenderCopy(renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip()
{
    SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
    return renderer;
}