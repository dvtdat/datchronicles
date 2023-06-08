#ifndef DOOR_H
#define DOOR_H

#include <string>

#include "rectangle.h"
#include "global.h"

class Door : public Rectangle
{
private:
    std::string destination;
public:
    Door();
    Door(Rectangle r, std::string destination): 
        Rectangle(r.getLeft() * globals::SPRITE_SCALE, r.getTop() * globals::SPRITE_SCALE,
        r.getWidth() * globals::SPRITE_SCALE, r.getHeight() * globals::SPRITE_SCALE), destination(destination) {};
    
    const inline Rectangle getRectangle() const { return getRect(); }
    const inline std::string getDestination() const { return destination; }
    
};

#endif // DOOR_H