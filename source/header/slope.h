#ifndef SLOPE_H
#define SLOPE_H

#include <math.h>

#include "global.h"
#include "rectangle.h"

class Slope
{
private:
    Vector2 p1, p2;
    float slope;
public:
    Slope() {}
    Slope(Vector2 p1, Vector2 p2): p1(p1), p2(p2)
    {
        if (p2.x - p1.x != 0)
        {
            slope = (fabs(p2.y) - fabs(p1.y)) / (fabs(p2.x) - fabs(p1.x));
        }
    }

    const bool collidesWith(const Rectangle &other) const
    {
        return  (other.getRight() >= p2.x && other.getLeft() <= p1.x && other.getTop() <= p2.y && other.getBottom() >= p1.y) || 
                (other.getRight() >= p1.x && other.getLeft() <= p2.x && other.getTop() <= p1.y && other.getBottom() >= p2.y) ||
                (other.getRight() >= p2.x && other.getLeft() <= p1.x && other.getTop() <= p1.y && other.getBottom() >= p2.y) ||
                (other.getRight() >= p1.x && other.getLeft() <= p2.x && other.getTop() <= p2.y && other.getBottom() >= p1.y);
    }

    const inline Vector2 getP1() { return p1; }
    const inline Vector2 getP2() { return p2; }
    const inline float getSlope() const { return slope; }
};

#endif // SLOPE_H