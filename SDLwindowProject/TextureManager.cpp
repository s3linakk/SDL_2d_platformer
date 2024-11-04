#include "TextureManager.h"
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::loadTexture(const std::string& file, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(file.c_str());
    if (tempSurface == nullptr) {
        std::cerr << "Ошибка загрузки изображения: " << IMG_GetError() << std::endl;
        return nullptr;
    }


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    if (!texture) {
        std::cerr << "Ошибка создания текстуры: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    else {
        SDL_FreeSurface(tempSurface);
        return texture;
    }


}
