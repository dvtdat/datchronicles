#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "animatedsprite.h"
#include "global.h"
#include "slope.h"

class Graphics;

class Player : public AnimatedSprite
{
private:
    float dx, dy;
    Direction facing;
    bool grounded;
    bool lookingUp, lookingDown;
    int maxHP, currentHP;
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    ~Player();

    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveLeft();
    void moveRight();
    void stopMoving();
    
    void lookUp();
    void stopLookingUp();
    void loopDown();
    void stopLookingDown();
    
    void jump();

    virtual void animationDone(std::string currentAnimation);
    virtual void setUpAnimation();

    void handleTileCollision(std::vector<Rectangle> &others);
    void handleSlopeCollision(std::vector<Slope> &others);

    const float getX() const;
    const float getY() const;

    const inline int getMaxHP() const { return maxHP; }
    const inline int getCurrentHP() const { return currentHP; }
};

#endif // PLAYER_H