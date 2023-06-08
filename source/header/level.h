#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

#include "sprite.h"
#include "global.h"
#include "tile.h"
#include "rectangle.h"
#include "slope.h"
#include "animatedtile.h"
#include "door.h"

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
    std::vector<Slope> slopes;

    std::vector<AnimatedTile> animatedTileList;
    std::vector<AnimatedTileInfo> animatedTileInfoList;

    std::vector<Door> doorList;

    void loadMap(std::string mapName, Graphics &graphics);

    Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);

public:
    Level();
    Level(std::string mapName, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);

    std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
    std::vector<Slope> checkSlopeCollisions(const Rectangle &other);
    std::vector<Door> checkDoorCollisions(const Rectangle &other);
    const Vector2 getPlayerSpawnPoint() const;
};

struct Tileset
{
    SDL_Texture* texture;
    int firstGid;
    Tileset(): firstGid(-1) {}
    Tileset(SDL_Texture* texture, int firstGid): texture(texture), firstGid(firstGid) {}
};

#endif // LEVEL_H