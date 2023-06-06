#ifndef LEVEL_H
#define LEVEL_H

#include <string>

#include "sprite.h"
#include "global.h"

class Graphics;
struct SDL_Texture;

class Level
{
private:
    std::string mapName;
    Vector2 spawnPoint;
    Vector2 size;
    SDL_Texture* backgroundTexture;

    void loadMap(std::string mapName, Graphics &graphics);

public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);
};

#endif // LEVEL_H