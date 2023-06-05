#ifndef GAME_H
#define GAME_H

#include "..\src\animatedsprite.cpp"
#include "..\src\sprite.cpp"

class Graphics;

class Game
{
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    AnimatedSprite player;
public:
    Game();
    ~Game();
};

#endif // GAME_H