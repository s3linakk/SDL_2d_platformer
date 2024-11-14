#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "Platform.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <iostream>
#include <vector>
#include "Camera.h"
#include "BackgroundAnimation.h"
#include "MainMenu.h"

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
    Camera* camera;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Player* player;
    std::vector<Platform*> platforms; // Вектор для хранения платформ
    BackgroundAnimation* blackHoleAnimation;
    MainMenu* mainMenu;
};

#endif
