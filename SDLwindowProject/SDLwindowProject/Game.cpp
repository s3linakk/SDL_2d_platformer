#include "Game.h"
#include <iostream>
#include "Constants.h"
#include "MainMenu.h"

Game::Game()
    : window(nullptr), renderer(nullptr), isRunning(false), player(nullptr), platforms(), camera(), mainMenu(nullptr) {}

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

    // ������������� ����
    mainMenu = new MainMenu(renderer);

    // ������� ������
    camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    // �������� ������� � ������������� ��������
    player = new Player("\\image\\ARRRR.png", "\\image\\p_wa_02_sh4.png", "\\image\\ARRRR.png", renderer);
    blackHoleAnimation = new BackgroundAnimation("\\image\\1335091370.png", renderer, 400, 400, 20, -400, -400, 1500, 1500);

    // ��������� ��������� � ������� ������������ �� ��������
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 100, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 190, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 280, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 370, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 460, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 550, 500, 96, 22 }));
    platforms.emplace_back(new Platform("\\image\\oak_woods_tileset.png", renderer, { 0, 0, 96, 22 }, { 640, 500, 96, 22 }));

    isRunning = true;
    return true;
}

void Game::run() {
    const int FPS = 120;                   // ������� FPS
    const int frameDelay = 2000 / FPS;    // ����� �� ���� � ������������� (�������� 16.67 �� ��� 60 FPS)

    // ���� ��� ������ ���� ����� ������� ����
    while (mainMenu->isActive()) {
        mainMenu->handleEvents();
        mainMenu->update();

        SDL_RenderClear(renderer);
        mainMenu->render();  // ������������ ����
        SDL_RenderPresent(renderer);
    }

    // �������� ������� ����
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
    bool playerOnPlatform = false;
    blackHoleAnimation->update();

    // �������� �������� ������ � ������ ����������
    for (const auto& platform : platforms) {
        if (player->checkCollision(player->getRect(), platform->getRect())) {
            player->handlePlatformCollision(platform->getRect());
            playerOnPlatform = true;
            break;
        }
    }

    // ���� �� ����� �������� ���, �� ����� ������
    if (!playerOnPlatform) {
        player->setOnGround(false);
    }
    player->update(platforms[0]->getRect());
    camera->update(player->getRect(), LEVEL_WIDTH, LEVEL_HEIGHT);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    // ������� �������� �������� ������ ����, ��� ���
    blackHoleAnimation->render(renderer);

    for (Platform* platform : platforms) {
        platform->render(renderer, camera->cameraRect);
    }

    player->render(renderer, camera->cameraRect);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    for (Platform* platform : platforms) {
        delete platform;
    }
    platforms.clear();

    delete player;
    delete blackHoleAnimation;
    delete mainMenu; // ����������� ������ ��� ����

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
