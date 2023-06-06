#include "../header/input.h"

// Reset irrelevant keys in new frame
void Input::beginNewFrame()
{
    pressKeys.clear();
    releasedKeys.clear();
}

// Called when a key being pressed
void Input::keyDownEvent(const SDL_Event& event)
{
    pressKeys[event.key.keysym.scancode] = true;
    heldKeys[event.key.keysym.scancode] = true;
}

// Called when a key is released
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