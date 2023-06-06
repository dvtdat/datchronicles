#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "global.h"

class Rectangle
{
private:
    int x;
    int y;
    int width;
    int height;
public:
    Rectangle() {}
    Rectangle(int x, int y, int width, int height): x(x), y(y), width(width), height(height) {};

    const int getCenterX() const { return x + width / 2; }
    const int getCenterY() const { return y + height / 2; }

    const int getLeft() const { return x; }
    const int getRight() const { return x + width; }
    const int getTop() const { return y; }
    const int getBottom() const { return y + height; }

    const int getWidth() const { return width; }
    const int getHeight() const { return height; }

    const int getSide(const sides::Side side) const
    {
        return  side == sides::LEFT ? getLeft() :
                side == sides::RIGHT ? getRight() :
                side == sides::TOP ? getTop() :
                side == sides::BOTTOM ? getBottom() : sides::NONE;
    }

    const bool collidesWith(const Rectangle &other) const
    {
        return getRight() >= other.getLeft() && getLeft() <= other.getRight() 
                && getTop() <= other.getBottom() && getBottom() >= other.getTop();
    }

    const bool isValidRectangle() const
    {
        return (x >= 0 && y >= 0 && width >= 0 && height >= 0);
    }
};

#endif // RECTANGLE_H