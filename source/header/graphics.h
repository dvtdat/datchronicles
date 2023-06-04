#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    Graphics();
    ~Graphics();
};

#endif // GRAPHICS_H