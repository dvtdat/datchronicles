#include <SDL2/SDL.h>

#include "..\header\animatedtile.h"
#include "..\header\tile.h"
#include "..\header\graphics.h"

AnimatedTile::AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture* tileset, Vector2 size, Vector2 postion):
    Tile(tileset, size, tilesetPosition.at(0), postion)
{
    this->tilesetPosition = tilesetPosition;
    this->duration = duration;
    this->tileToDraw = 0;
}

void AnimatedTile::update(int elapsedTime)
{
    if (amountOfTime <= 0)
    {
        if (tileToDraw == tilesetPosition.size() - 1)
        {
            tileToDraw = 0;
        }
        else tileToDraw++;
        amountOfTime = duration;
    }
    else amountOfTime -= elapsedTime;

    Tile::update(elapsedTime);
}

void AnimatedTile::draw(Graphics &graphics)
{
    SDL_Rect destRect;
    destRect.x = position.x;
    destRect.y = position.y;
    destRect.w = size.x * globals::SPRITE_SCALE;
    destRect.h = size.y * globals::SPRITE_SCALE;

    SDL_Rect sourceRect;
    sourceRect.x = tilesetPosition.at(tileToDraw).x;
    sourceRect.y = tilesetPosition.at(tileToDraw).y;
    sourceRect.w = size.x;
    sourceRect.h = size.y;

    graphics.blitSurface(tileset, &sourceRect, &destRect);
}