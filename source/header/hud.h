#ifndef HUD_H
#define HUD_H

#include "sprite.h"

class Graphics;
class Player;

class HUD
{
private:
    Player player;
    Sprite healthBarSprite;
    Sprite healthNumber1;
    Sprite currentHealthBar;

    Sprite levelWord;
    Sprite levelNumber;
    Sprite expBar;
    
    Sprite slash;
    Sprite dashes;

public:
    HUD();
    HUD(Graphics &graphics, Player &player);

    void update(int elapsedTime);
    void draw(Graphics &graphics);
};

#endif // HUD_H