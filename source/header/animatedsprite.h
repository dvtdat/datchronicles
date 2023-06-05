#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>
#include <vector>

#include "sprite.h"
#include "global.h"

class Graphics;

class AnimatedSprite : public Sprite
{
private:
    std::map<std::string, std::vector<SDL_Rect>> animations;
    std::map<std::string, Vector2> offsets;
    int frameIndex;
    double timeElapsed;
    bool visible;
protected:
    double timeToUpdate;
    bool currentAnimationOnce;
    std::string currentAnimation;

    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offsets);
    void resetAnimation();
    void stopAnimation();
    void setVisible(bool visible);
    virtual void animationDone(std::string currentAnimation);
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath, 
        int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);
    void playAnimation(std::string animation, bool once = false);
    void update(int elapsedTime);
    void draw(Graphics &graphics, int x, int y);
    virtual void setUpAnimation();
};

#endif // ANIMATED_SPRITE_H