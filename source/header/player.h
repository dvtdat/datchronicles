#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "animatedsprite.h"
#include "global.h"

class Graphics;

class Player : public AnimatedSprite
{
private:
    float dx, dy;
    Direction facing;
public:
    Player();
    Player(Graphics &graphics, float x, float y);
    ~Player();

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveLeft();
    void moveRight();
    void stopMoving();

    virtual void animationDone(std::string currentAnimation);
    virtual void setUpAnimation();
};

#endif // PLAYER_H