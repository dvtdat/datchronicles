#include "..\header\player.h"
#include "..\header\graphics.h"

namespace playerconstant
{
    const float WALK_SPEED = 0.2f;
    const float JUMP_SPEED = 0.7f;

    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
};

Player::Player()
{

}

Player::Player(Graphics &graphics, Vector2 spawnPoint):
    AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
    dx(0), dy(0), facing(RIGHT), grounded(false)
{
    graphics.loadImage("content/sprites/MyChar.png");
    setUpAnimation();
    playAnimation("RunLeft");
}

Player::~Player()
{

}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, x, y);
}

void Player::update(float elapsedTime)
{
    if (dy <= playerconstant::GRAVITY_CAP)
    {
        dy += playerconstant::GRAVITY * elapsedTime;
    }

    x += dx * elapsedTime;
    y += dy * elapsedTime;
    
    AnimatedSprite::update(elapsedTime);
}

void Player::animationDone(std::string currentAnimation)
{

}

void Player::setUpAnimation()
{
    addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
    addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
    addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
    addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
}

void Player::moveLeft()
{
    dx = -playerconstant::WALK_SPEED;
    playAnimation("RunLeft");
    facing = LEFT;
}

void Player::moveRight()
{
    dx = playerconstant::WALK_SPEED;
    playAnimation("RunRight");
    facing = RIGHT;
}

void Player::stopMoving()
{
    dx = 0.0f;
    playAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::jump()
{
    if (!grounded) return;
    dy = 0;
    dy -= playerconstant::JUMP_SPEED;
    grounded = false;
}

void Player::handleTileCollision(std::vector<Rectangle> &others)
{
    for (int i = 0; i < others.size(); ++i)
    {
        sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
        if (collisionSide != sides::NONE)
        {
            if (collisionSide == sides::TOP)
            {
                dy = 0;
                y = others.at(i).getBottom() + 1;
                if (grounded)
                {
                    dx = 0;
                    x -= facing == RIGHT ? 1.0f : -1.0f;
                }
            }
            if (collisionSide == sides::BOTTOM) y = others.at(i).getTop() - boundingBox.getHeight() - 1, dy = 0, grounded = true;
            if (collisionSide == sides::LEFT) x = others.at(i).getRight() + 1;
            if (collisionSide == sides::RIGHT) x = others.at(i).getLeft() - boundingBox.getWidth() - 1;
        }
    }
}

void Player::handleSlopeCollision(std::vector<Slope> &others)
{
    for (int i = 0; i < others.size(); ++i)
    {
        int b = (others.at(i).getP1().y - (others.at(i).getSlope() * fabs(others.at(i).getP1().x)));

        int centerX = boundingBox.getCenterX();
        int newY = (others.at(i).getSlope() * centerX) + b - 8; // 8 is a magic number, don't ask me why

        if (grounded)
        {
            y = newY - boundingBox.getHeight();
            grounded = true;
        }
    }
}

const float Player::getX() const
{
    return x;
}

const float Player::getY() const
{
    return y;
}
