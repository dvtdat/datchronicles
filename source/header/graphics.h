#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::map<std::string, SDL_Surface*> spriteSheet;
public:
    Graphics();
    ~Graphics();
    SDL_Surface* loadImage(const std::string &filePath);
    void blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
    void flip();
    void clear();
    SDL_Renderer* getRenderer() const;

};

#endif // GRAPHICS_H