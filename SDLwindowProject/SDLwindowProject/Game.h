#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "Platform.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <iostream>
#include <vector>

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int width, int height);
    void run();
    void handleEvents();
    void update();
    void render();
    void clean();

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Player* player;
    std::vector<Platform*> platforms; // Вектор для хранения платформ
};

#endif
