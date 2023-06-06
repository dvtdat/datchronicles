#include "..\header\level.h"
#include "..\header\global.h"
#include "..\header\graphics.h"

Level::Level()
{

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics): mapName(mapName), spawnPoint(spawnPoint), size(Vector2(0, 0))
{
    loadMap(mapName, graphics);
}

Level::~Level()
{

}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
    backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("content/backgrounds/bkBlue.png"));
    size = Vector2(1280, 960);
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
    SDL_Rect sourceRect = {0, 0, 64, 64};
    SDL_Rect destinationRect;

    for (int x = 0; x < size.x / 64; ++x)
    {
        for (int y = 0; y < size.x / 64; ++y)
        {
            destinationRect.x = x * 64 * globals::SPRITE_SCALE;
            destinationRect.y = y * 64 * globals::SPRITE_SCALE;
            destinationRect.w = 64 * globals::SPRITE_SCALE;
            destinationRect.h = 64 * globals::SPRITE_SCALE;
            graphics.blitSurface(backgroundTexture, &sourceRect, &destinationRect);
        }
    }
}