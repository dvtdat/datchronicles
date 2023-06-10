#include <SDL2/SDL.h>
#include <iostream>

#include "graphics.cpp"
#include "input.cpp"
#include "..\header\game.h"

namespace 
{
    const int FPS = 50;
    const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
    Graphics graphics;
    Input input;
    SDL_Event event;

    level = Level("Map0", graphics);
    player = Player(graphics, level.getPlayerSpawnPoint());
    hud = HUD(graphics, player);

    int LAST_UPDATE_TIME = SDL_GetTicks();

    while (true)
    {
        input.beginNewFrame();

        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.repeat == 0)
                {
                    input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                input.keyUpEvent(event);
            }
            else if (event.type == SDL_QUIT)
            {
                return;
            }
        }

        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            return;
        }
        else if (input.isKeyHeld(SDL_SCANCODE_A))
        {
            player.moveLeft();
        }
        else if (input.isKeyHeld(SDL_SCANCODE_D))
        {
            player.moveRight();
        }

        if (input.isKeyHeld(SDL_SCANCODE_W))
        {
            player.lookUp();
        }
        else if (input.isKeyHeld(SDL_SCANCODE_S))
        {
            player.loopDown();
        }

        if (input.wasKeyReleased(SDL_SCANCODE_W))
        {
            player.stopLookingUp();
        }

        if (input.wasKeyReleased(SDL_SCANCODE_S))
        {
            player.stopLookingDown();
        }

        if (input.wasKeyPressed(SDL_SCANCODE_SPACE))
        {
            player.jump();
        }

        if (input.isKeyHeld(SDL_SCANCODE_SPACE) && player.isGrounded())
        {
            player.jump();
        }
        
        if (!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D))
        {
            player.stopMoving();
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME), graphics);
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        
        draw(graphics);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();
    level.draw(graphics); // Level get drawn before Player -> Player is on the upper layer
    player.draw(graphics);
    hud.draw(graphics);
    graphics.flip();
}

void Game::update(float elapsedTime, Graphics &graphics)
{
    player.update(elapsedTime);
    level.update(elapsedTime);
    hud.update(elapsedTime);
    std::vector<Rectangle> othersRect = level.checkTileCollisions(player.getBoundingBox());
    if (othersRect.size() > 0)
    {
        player.handleTileCollision(othersRect);
    }

    std::vector<Slope> othersSlope = level.checkSlopeCollisions(player.getBoundingBox());
    if (othersSlope.size() > 0)
    {
        player.handleSlopeCollision(othersSlope);
    }

    std::vector<Door> othersDoor = level.checkDoorCollisions(player.getBoundingBox());
    if (othersDoor.size() > 0)
    {
        player.handleDoorCollision(othersDoor, level, graphics);
    }
}
