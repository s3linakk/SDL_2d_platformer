#include "Game.h"
#include <iostream>

Game::Game() : window(nullptr), renderer(nullptr), isRunning(false), player(nullptr), platforms() {}

Game::~Game() {
    clean();
}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "������ ������������� SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "������ �������� ����: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "������ �������� ���������: " << SDL_GetError() << std::endl;
        return false;
    }

    // �������� ������� � ������������� ��������
    player = new Player("\\image\\ARRRR.png", "\\image\\p_wa_02_sh4.png", "\\image\\ARRRR.png", renderer);

    // ��������� ��������� � ������� ������������ �� ��������
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 100, 500, 1000, 50 }));
   

    isRunning = true;
    return true;
}

void Game::run() {
    const int FPS = 60;                   // ������� FPS
    const int frameDelay = 1000 / FPS;    // ����� �� ���� � ������������� (�������� 16.67 �� ��� 60 FPS)

    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks(); // ����� ������ �����

        handleEvents();
        update();
        render();

        // �����, ����������� �� ��������� �����
        int frameTime = SDL_GetTicks() - frameStart;

        // ���� ���� ��� ��������� �������, ��� ������� �����, ��������� ��������
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::handleEvents() {
    InputHandler::getInstance().update();
    if (InputHandler::getInstance().isQuit()) {
        isRunning = false;
    }
}

void Game::update() {
    for (Platform* platform : platforms) {
        if (player->checkCollision(player->getRect(), platform->getRect())) {
            // ������ ��������� �������� (���� �����)
        }
    }
    player->update(platforms[0]->getRect());
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    for (Platform* platform : platforms) {
        platform->render(renderer);
    }

    player->render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    for (Platform* platform : platforms) {
        delete platform;
    }
    platforms.clear();

    delete player;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
