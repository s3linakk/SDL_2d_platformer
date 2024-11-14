#pragma once
#include <SDL.h>
#include <vector>
#include <string>

class MainMenu {
public:
    MainMenu(SDL_Renderer* renderer);
    ~MainMenu();

    void render();         // Отрисовка меню
    void handleEvents();   // Обработка ввода пользователя
    bool isActive() const; // Возвращает true, если меню активно
    void update();         // Обновление меню

private:
    SDL_Renderer* renderer;
    bool active;           // Флаг активности меню
    int selectedItem;      // Индекс выбранного пункта меню

    std::vector<std::string> menuItems; // Пункты меню
    SDL_Color activeColor;              // Цвет выделенного пункта
    SDL_Color inactiveColor;            // Цвет остальных пунктов
};