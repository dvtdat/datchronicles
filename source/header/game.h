#ifndef GAME_H
#define GAME_H

#include "..\src\animatedsprite.cpp"
#include "..\src\sprite.cpp"
#include "..\src\player.cpp"
#include "..\src\level.cpp"
#include "..\src\hud.cpp"

class Graphics;

class Game
{
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    Player player;
    Level level;
    HUD hud;
public:
    Game();
    ~Game();
};

#endif // GAME_H