#ifndef GAME_H
#define GAME_H

class Graphics;

class Game
{
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);
public:
    Game();
    ~Game();
};

#endif // GAME_H