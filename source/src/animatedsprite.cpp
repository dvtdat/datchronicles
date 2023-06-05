#include <SDL2/SDL.h>
#include <iostream>

#include "..\header\animatedsprite.h"
#include "..\header\graphics.h"
#include "..\header\global.h"

AnimatedSprite::AnimatedSprite()
{

}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, 
    int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate):
        Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY)
{
    this->frameIndex = 0;
    this->timeElapsed = 0.0;
    this->timeToUpdate = timeToUpdate;
    this->visible = true;
    this->currentAnimationOnce = false;
    this->currentAnimation = "";
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offsets)
{
    std::vector<SDL_Rect> rectangles;
    for (int i = 0; i < frames; ++i)
    {
        SDL_Rect tmpRect = { (i + x) * width, y, width, height};
        rectangles.push_back(tmpRect);
    }
    this->animations.insert({name, rectangles});
    this->offsets.insert({name, offsets});
}

void AnimatedSprite::resetAnimation()
{
    animations.clear();
    offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
    currentAnimationOnce = once;
    if (currentAnimation != animation)
    {
        currentAnimation = animation;
        frameIndex = 0;
    }
}

void AnimatedSprite::setVisible(bool visible)
{
    this->visible = visible;
}

void AnimatedSprite::stopAnimation()
{
    frameIndex = 0;
    animationDone(currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
    Sprite::update();
    timeElapsed += elapsedTime;
    if (timeElapsed > timeToUpdate)
    {
        timeElapsed -= timeToUpdate;
        if (frameIndex < (int)animations[currentAnimation].size() - 1)
        {
            frameIndex++;
        }
        else
        {
            if (currentAnimationOnce == true)
            {
                setVisible(false);
            }
            frameIndex = 0;
            animationDone(currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
    if (visible)
    {
        SDL_Rect destinationRectangle;
        destinationRectangle.x = x + offsets[currentAnimation].x;
        destinationRectangle.y = y + offsets[currentAnimation].y;
        destinationRectangle.w = sourceRect.w * globals::SPRITE_SCALE;
        destinationRectangle.h = sourceRect.h * globals::SPRITE_SCALE;

        SDL_Rect tmpSourceRect = animations[currentAnimation][frameIndex];
        graphics.blitSurface(spriteSheet, &tmpSourceRect, &destinationRectangle);
    }
}

void AnimatedSprite::animationDone(std::string currentAnimation)
{

}

void AnimatedSprite::setUpAnimation()
{
    addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
}