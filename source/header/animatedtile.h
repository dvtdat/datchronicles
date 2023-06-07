#ifndef ANIMATED_TILE_H
#define ANIMATED_TILE_H

#include <vector>

#include "tile.h"

class AnimatedTile : public Tile
{
private:
    std::vector<Vector2> tilesetPosition;
    int tileToDraw;
    int duration;
protected:
    int amountOfTime = 0;
    int notDone = false;
public:
    AnimatedTile(std::vector<Vector2> tilesetPosition, int duration, SDL_Texture* tileset, Vector2 size, Vector2 postion);
    void update(int elapsedTime);
    void draw(Graphics &graphics);
};

struct AnimatedTileInfo
{
public:
    int tilesetsFirstGid;
    int startTileID;
    std::vector<int> tileIDs;
    int duration;
};

#endif // ANIMATED_TILE_H