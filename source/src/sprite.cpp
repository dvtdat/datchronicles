#include <SDL2/SDL.h>

#include "..\header\sprite.h"
#include "..\header\graphics.h"
#include "..\header\global.h"

Sprite::Sprite()
{

}

Sprite::Sprite(Graphics &graphics, const std::string &filePath,
    int sourceX, int sourceY, int width, int height, float posX, float posY): x(posX), y(posY)
{
    sourceRect.x = sourceX;
    sourceRect.y = sourceY;
    sourceRect.w = width;
    sourceRect.h = height;

    spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (spriteSheet == NULL)
    {
        std::cout << "[ERROR] Unable to load image\n";
    }

    boundingBox = Rectangle(x, y, width * globals::SPRITE_SCALE, height * globals::SPRITE_SCALE);
}

Sprite::~Sprite()
{

}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destinationRectangle = {x, y, (int)(sourceRect.w * globals::SPRITE_SCALE), (int)(sourceRect.h * globals::SPRITE_SCALE)};
    graphics.blitSurface(spriteSheet, &sourceRect, &destinationRectangle);
}

void Sprite::update()
{
    boundingBox = Rectangle(x, y, sourceRect.w * globals::SPRITE_SCALE, sourceRect.h * globals::SPRITE_SCALE);
}

const Rectangle Sprite::getBoundingBox() const
{
    return boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const
{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = getBoundingBox().getRight() - other.getLeft();
    amtLeft = other.getRight() - getBoundingBox().getLeft();
    amtTop = other.getBottom() - getBoundingBox().getTop();
    amtBottom = getBoundingBox().getBottom() - other.getTop();

    int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
    int lowest = vals[0];
    for (int i = 0; i < 4; ++i)
    {
        if (vals[i] < lowest)
        {
            lowest = vals[i];
        }
    }

    return  lowest == abs(amtRight) ? sides::RIGHT :
            lowest == abs(amtLeft) ? sides::LEFT :
            lowest == abs(amtTop) ? sides::TOP :
            lowest == abs(amtBottom) ? sides::BOTTOM : sides::NONE;
}

void Sprite::setSourceRectX(int value)
{
    sourceRect.x = value;
}

void Sprite::setSourceRectY(int value)
{
    sourceRect.y = value;
}

void Sprite::setSourceRectW(int value)
{
    sourceRect.w = value;
}

void Sprite::setSourceRectH(int value)
{
    sourceRect.h = value;
}