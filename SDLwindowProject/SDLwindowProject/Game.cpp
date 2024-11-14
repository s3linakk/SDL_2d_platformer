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
        std::cerr << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Ошибка создания рендерера: " << SDL_GetError() << std::endl;
        return false;
    }

    // Инициализация меню
    mainMenu = new MainMenu(renderer);

    // Создаем камеру
    camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Загрузка текстур и инициализация объектов
    player = new Player("\\image\\ARRRR.png", "\\image\\p_wa_02_sh4.png", "\\image\\ARRRR.png", renderer);
    blackHoleAnimation = new BackgroundAnimation("\\image\\1335091370.png", renderer, 400, 400, 20, -400, -400, 1500, 1500);

    // Добавляем платформы с разными координатами из тайлсета
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
    const int FPS = 120;                   // Целевой FPS
    const int frameDelay = 2000 / FPS;    // Время на кадр в миллисекундах (примерно 16.67 мс для 60 FPS)

    // Цикл для показа меню перед началом игры
    while (mainMenu->isActive()) {
        mainMenu->handleEvents();
        mainMenu->update();

        SDL_RenderClear(renderer);
        mainMenu->render();  // Отрисовываем меню
        SDL_RenderPresent(renderer);
    }

    // Основной игровой цикл
    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks(); // Время начала кадра

        handleEvents();
        update();
        render();

        // Время, потраченное на обработку кадра
        int frameTime = SDL_GetTicks() - frameStart;

        // Если кадр был обработан быстрее, чем целевое время, добавляем задержку
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

    // Проверка коллизий игрока с каждой платформой
    for (const auto& platform : platforms) {
        if (player->checkCollision(player->getRect(), platform->getRect())) {
            player->handlePlatformCollision(platform->getRect());
            playerOnPlatform = true;
            break;
        }
    }

    // Если ни одной коллизии нет, то игрок падает
    if (!playerOnPlatform) {
        player->setOnGround(false);
    }
    player->update(platforms[0]->getRect());
    camera->update(player->getRect(), LEVEL_WIDTH, LEVEL_HEIGHT);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 41, 41, 41, 255);
    SDL_RenderClear(renderer);

    // Сначала рендерим анимацию черной дыры, как фон
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
    delete mainMenu; // Освобождаем память под меню

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
