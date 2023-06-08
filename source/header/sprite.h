#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

#include "rectangle.h"
#include "global.h"

class Graphics;

class Sprite
{
protected:
    float x, y;
    SDL_Rect sourceRect;
    SDL_Texture* spriteSheet;
    Rectangle boundingBox;
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, 
        int sourceX, int sourceY, int width, int height, float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);

    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;

    const inline float getX() const { return x; }
    const inline float getY() const { return y; }

    void setSourceRectX(int value);
    void setSourceRectY(int value);
    void setSourceRectW(int value);
    void setSourceRectH(int value);
};

#endif // SPRITE_H