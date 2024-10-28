#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SDL.h>
#include <iostream>

enum class PlayerState { IDLE, WALK, JUMP };

class Player {
public:

    Player(const std::string& idleTexturePath, const std::string& walkTexturePath, const std::string& jumpTexturePath, SDL_Renderer* renderer);
    ~Player();

    void update(const SDL_Rect& platformRect);
    void render(SDL_Renderer* renderer);

    SDL_Rect getRect() const { return rect; } // Добавляем этот метод

    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

private:
    SDL_Texture* idleTexture;
    SDL_Texture* walkTexture;
    SDL_Texture* jumpTexture;
    SDL_Texture* currentTexture;

    SDL_Rect idleFrameRect;
    SDL_Rect walkFrameRect;
    SDL_Rect jumpFrameRect;

    SDL_Rect rect;
    int velX, velY;
    bool onGround;
    int frame;
    int direction;

    PlayerState state; // Текущее состояние игрока

};

#endif
