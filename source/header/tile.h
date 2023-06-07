#ifndef TILE_H
#define TILE_H

#include "global.h"

struct SDL_Texture;
class Graphics;

class Tile
{
protected:
    SDL_Texture* tileset;
    Vector2 size;
    Vector2 tilesetPosition;
    Vector2 position;
public:
    Tile();
    Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
    void update(int elapsedTime);
    void draw(Graphics &graphics);
};

#endif // TILE_H