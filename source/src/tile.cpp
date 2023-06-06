#include "..\header\tile.h"
#include "..\header\graphics.h"

Tile::Tile()
{

}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position):
    tileset(tileset), size(size), tilesetPosition(tilesetPosition),
    position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE))
{

}

void Tile::update(int elapsedTime)
{

}

void Tile::draw(Graphics &graphics)
{
    SDL_Rect sourceRect = {tilesetPosition.x, tilesetPosition.y, size.x, size.y};
    
    SDL_Rect destinationRect;
    destinationRect.x = position.x;
    destinationRect.y = position.y;
    destinationRect.w = size.x * globals::SPRITE_SCALE;
    destinationRect.h = size.y * globals::SPRITE_SCALE;

    graphics.blitSurface(tileset, &sourceRect, &destinationRect);
}