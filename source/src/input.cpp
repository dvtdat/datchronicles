#include "../header/input.h"

void Input::beginNewFrame()
{
    pressKeys.clear();
    releasedKeys.clear();
}

void Input::keyDownEvent(const SDL_Event& event)
{
    pressKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event)
{
    releasedKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = false;
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return heldKeys[key];
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return pressKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
    return releasedKeys[key];
}