#pragma once
#include <SDL.h>
#include <string>

class BackgroundAnimation {
public:
    BackgroundAnimation(const std::string& texturePath, SDL_Renderer* renderer, int frameWidth, int frameHeight, int frameCount, int x, int y, int width, int height);
    ~BackgroundAnimation();

    void update();  // Обновляет текущий кадр
    void render(SDL_Renderer* renderer);  // Отрисовывает текущий кадр

private:
    SDL_Texture* texture;  // Текстура с кадрами анимации
    int currentFrame;  // Текущий кадр
    int frameDelay;  // Задержка между кадрами
    Uint32 lastFrameTime;  // Время последнего кадра

    int frameWidth;  // Ширина одного кадра
    int frameHeight; // Высота одного кадра
    int frameCount;  // Общее количество кадров
    SDL_Rect destRect;  // Прямоугольник для отображения
};