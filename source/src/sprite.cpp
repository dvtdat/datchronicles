#include <SDL2/SDL.h>

#include "..\header\sprite.h"
#include "..\header\graphics.h"

Sprite::Sprite()
{

}

Sprite::Sprite(Graphics &graphics, const std::string &filePath,
    int sourceX, int sourceY, int width, int height, float posX, float posY): x(posX), y(posY)
{
    sourceRect.x = sourceX;
    sourceRect.y = sourceY;
    sourceRect.w = width;
    sourceRect.h = height;

    spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (spriteSheet == NULL)
    {
        printf("\nError: Unable to load img...\n");
    } 
}

Sprite::~Sprite()
{

}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destinationRectangle = {x , y, sourceRect.w, sourceRect.h};
    graphics.blitSurface(spriteSheet, &sourceRect, &destinationRectangle);
}

void Sprite::update()
{

}