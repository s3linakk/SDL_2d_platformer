#include "Platform.h"
#include "TextureManager.h"
#include <iostream>

Platform::Platform(const std::string& texturePath, SDL_Renderer* renderer, const SDL_Rect& srcRect, const SDL_Rect& destRect)
    : srcRect(srcRect), destRect(destRect) {
    texture = TextureManager::loadTexture(texturePath, renderer);
}

Platform::~Platform() {
    SDL_DestroyTexture(texture);
}

void Platform::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}