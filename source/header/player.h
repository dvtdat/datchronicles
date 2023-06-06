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
    bool grounded;
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    ~Player();

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveLeft();
    void moveRight();
    void stopMoving();

    virtual void animationDone(std::string currentAnimation);
    virtual void setUpAnimation();

    void handleTileCollision(std::vector<Rectangle> &others);

    const float getX() const;
    const float getY() const;
};

#endif // PLAYER_H