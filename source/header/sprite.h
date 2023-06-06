#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

#include <string>

class Graphics;

class Sprite
{
protected:
    float x, y;
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, 
        int sourceX, int sourceY, int width, int height, float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);
};

#endif // SPRITE_H