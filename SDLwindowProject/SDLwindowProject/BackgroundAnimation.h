#pragma once
#include <SDL.h>
#include <string>

class BackgroundAnimation {
public:
    BackgroundAnimation(const std::string& texturePath, SDL_Renderer* renderer, int frameWidth, int frameHeight, int frameCount, int x, int y, int width, int height);
    ~BackgroundAnimation();

    void update();  // ��������� ������� ����
    void render(SDL_Renderer* renderer);  // ������������ ������� ����

private:
    SDL_Texture* texture;  // �������� � ������� ��������
    int currentFrame;  // ������� ����
    int frameDelay;  // �������� ����� �������
    Uint32 lastFrameTime;  // ����� ���������� �����

    int frameWidth;  // ������ ������ �����
    int frameHeight; // ������ ������ �����
    int frameCount;  // ����� ���������� ������
    SDL_Rect destRect;  // ������������� ��� �����������
};