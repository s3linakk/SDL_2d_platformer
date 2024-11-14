#ifndef PLATFORM_H
#define PLATFORM_H

#include <SDL.h>
#include <string>

class Platform {
public:
    Platform(const std::string& texturePath, SDL_Renderer* renderer, const SDL_Rect& srcRect, const SDL_Rect& destRect);
    ~Platform();

    void render(SDL_Renderer* renderer, const SDL_Rect& cameraRect);

    SDL_Rect getRect() const { return destRect; }

private:
    SDL_Texture* texture;
    SDL_Rect srcRect;   // Область текстуры, выбранная из тайлсета
    SDL_Rect destRect;  // Положение платформы на экране
};

#endif
