#include "BackgroundAnimation.h"
#include "TextureManager.h"

BackgroundAnimation::BackgroundAnimation(const std::string& texturePath, SDL_Renderer* renderer, int frameWidth, int frameHeight, int frameCount, int x, int y, int width, int height)
    : currentFrame(0), frameDelay(150), lastFrameTime(0), frameWidth(frameWidth), frameHeight(frameHeight), frameCount(frameCount) {

    // ��������� �������� � ���������
    texture = TextureManager::loadTexture(texturePath, renderer);

    // ������ ���������� � ������� ����������� �� ������
    destRect = { x, y, width, height };
}

BackgroundAnimation::~BackgroundAnimation() {
    SDL_DestroyTexture(texture);
}

void BackgroundAnimation::update() {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - lastFrameTime;

    // ��������� ���� ������ ���� ������ ������ �������, ��� ��������
    if (elapsedTime >= frameDelay) {
        currentFrame = (currentTime / frameDelay) % frameCount;
        lastFrameTime = currentTime;  // ��������� ����� ���������� �����
    }
}

void BackgroundAnimation::render(SDL_Renderer* renderer) {
    // ���������� �������� ������������� ��� �������� �����
    SDL_Rect srcRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };

    // �������� ������� ���� �� �����
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
