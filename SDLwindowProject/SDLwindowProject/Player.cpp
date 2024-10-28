#include "Player.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <iostream>
#include "Constants.h"

Player::Player(const std::string& idleTexturePath, const std::string& walkTexturePath, const std::string& jumpTexturePath, SDL_Renderer* renderer)
    : rect{ 100, 100, 41, 127 }, velX(0), velY(0), onGround(false), frame(0), direction(1), state(PlayerState::IDLE) {

    idleTexture = TextureManager::loadTexture(idleTexturePath, renderer);
    walkTexture = TextureManager::loadTexture(walkTexturePath, renderer);
    jumpTexture = TextureManager::loadTexture(jumpTexturePath, renderer);

    // Определяем размеры кадров для каждой текстуры
    idleFrameRect = { 0, 0, 41, 127 };  // Один кадр IDLE
    walkFrameRect = { 0, 0, 75, 137 };  // Один кадр WALK
    jumpFrameRect = { 0, 0, 41, 127 };  // Один кадр JUMP (при необходимости)

    currentTexture = idleTexture;

    if (!currentTexture) {
        std::cerr << "Ошибка инициализации текстуры игрока" << std::endl;
        currentTexture = nullptr;
    }
}

    Player::~Player() {
        SDL_DestroyTexture(idleTexture);
        SDL_DestroyTexture(walkTexture);
        SDL_DestroyTexture(jumpTexture);
}


// Функция для проверки коллизии
bool Player::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x + a.w > b.x) && (a.x < b.x + b.w) &&
        (a.y + a.h > b.y) && (a.y < b.y + b.h);
}

void Player::update(const SDL_Rect& platformRect) {
    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    velX = 0;
    velY += 1;

    // Определяем начальное состояние
    PlayerState previousState = state;
    state = PlayerState::IDLE;

    if (keystate[SDL_SCANCODE_LEFT]) {
        velX = -5;
        direction = -1;
        state = PlayerState::WALK;
    }
    else if (keystate[SDL_SCANCODE_RIGHT]) {
        velX = 5;
        direction = 1;
        state = PlayerState::WALK;
    }

    if (keystate[SDL_SCANCODE_SPACE] && onGround) {
        velY = -15;
        onGround = false;
        state = PlayerState::JUMP;
    }

    if (state == PlayerState::WALK) {
        frame = (SDL_GetTicks() / 100) % 8;  // 8 кадров для WALK
    }
    else if (state == PlayerState::IDLE) {
        frame = (SDL_GetTicks() / 200) % 17;  // 4 кадра для IDLE, измените при необходимости
    }
    else if (state == PlayerState::JUMP) {
        frame = 0; // Один кадр для прыжка
    }

    // Обновляем позицию игрока
    rect.x += velX;

    if (rect.x < 0 || (rect.x + rect.w) > SCREEN_WIDTH) {
        rect.x -= velX;
    }

    rect.y += velY;


    // Проверка коллизии с платформой
    if (checkCollision(rect, platformRect)) {
        // Если произошла коллизия, игрок находится на платформе
        rect.y = platformRect.y - rect.h; // Устанавливаем игрока на платформу
        velY = 0; // Останавливаем падение
        onGround = true;
    }
    else {
        onGround = false; // Если нет коллизии, игрок снова падает
    }
}


void Player::render(SDL_Renderer* renderer) {
    SDL_Rect srcRect;
    int frameWidth;
    int frameHeight;

    switch (state) {
    case PlayerState::IDLE:
        currentTexture = idleTexture;
        srcRect = idleFrameRect;
        frameWidth = idleFrameRect.w;
        frameHeight = idleFrameRect.h;
        srcRect.x = frame * frameWidth;
        break;

    case PlayerState::WALK:
        currentTexture = walkTexture;
        srcRect = walkFrameRect;
        frameWidth = walkFrameRect.w;
        frameHeight = walkFrameRect.h;
        srcRect.x = frame * frameWidth;
        break;

    case PlayerState::JUMP:
        currentTexture = jumpTexture;
        srcRect = jumpFrameRect;
        frameWidth = jumpFrameRect.w;
        frameHeight = jumpFrameRect.h;
        srcRect.x = frame * frameWidth;
        break;
    }

    srcRect.w = frameWidth;
    srcRect.h = frameHeight;

    // Коррекция destRect по вертикали при разных размерах кадров
    int yOffset = rect.h - frameHeight;
    SDL_Rect destRect = { rect.x, rect.y + yOffset, frameWidth, frameHeight };

    SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &destRect, 0, nullptr,
        direction == 1 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}
