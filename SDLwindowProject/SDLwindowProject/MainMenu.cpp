// MainMenu.cpp
#include "MainMenu.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

MainMenu::MainMenu(SDL_Renderer* renderer)
    : renderer(renderer), active(true), selectedItem(0),
    activeColor{ 255, 0, 0, 255 }, inactiveColor{ 255, 255, 255, 255 } {

    // Инициализируем пункты меню
    menuItems = { "Start Game", "Options", "Exit" };

    // Проверяем, инициализирован ли TTF
    if (TTF_Init() == -1) {
        std::cerr << "Ошибка инициализации TTF: " << TTF_GetError() << std::endl;
    }
}

MainMenu::~MainMenu() {
    TTF_Quit();
}

void MainMenu::render() {
    TTF_Font* font = TTF_OpenFont("\\image\\silver.ttf", 24);
    if (!font) {
        std::cerr << "Ошибка загрузки шрифта: " << TTF_GetError() << std::endl;
        return;
    }

    int y = 200; // Начальная позиция по Y
    for (size_t i = 0; i < menuItems.size(); ++i) {
        SDL_Color color = (i == selectedItem) ? activeColor : inactiveColor;

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, menuItems[i].c_str(), color);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect = { 300, y, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        y += 50; // Расстояние между пунктами меню
    }

    TTF_CloseFont(font);
}

void MainMenu::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            active = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_UP:
                selectedItem = (selectedItem > 0) ? selectedItem - 1 : menuItems.size() - 1;
                break;
            case SDLK_DOWN:
                selectedItem = (selectedItem < menuItems.size() - 1) ? selectedItem + 1 : 0;
                break;
            case SDLK_RETURN:
                if (selectedItem == 0) {
                    active = false; // Старт игры
                }
                else if (selectedItem == 1) {
                    // Здесь может быть переход в меню настроек
                }
                else if (selectedItem == 2) {
                    SDL_Quit(); // Выход из игры
                    exit(0);
                }
                break;
            }
        }
    }
}

bool MainMenu::isActive() const {
    return active;
}

void MainMenu::update() {
    // Здесь можно добавлять анимации или звуки для меню
}
