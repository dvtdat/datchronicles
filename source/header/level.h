#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "sprite.h"
#include "global.h"
#include "tile.h"
#include "rectangle.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level
{
private:
    std::string mapName;
    Vector2 spawnPoint;
    Vector2 size;
    Vector2 tileSize;

    SDL_Texture* backgroundTexture;

    std::vector<Tile> tileList;
    std::vector<Tileset> tilesets;
    std::vector<Rectangle> collisionRects;

    void loadMap(std::string mapName, Graphics &graphics);

public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    const Vector2 getPlayerSpawnPoint() const;
};

struct Tileset
{
    SDL_Texture* Texture;
    int FirstGid;
    Tileset(): FirstGid(-1) {}
    Tileset(SDL_Texture* texture, int firstGid): Texture(texture), FirstGid(firstGid) {}
};

#endif // LEVEL_H