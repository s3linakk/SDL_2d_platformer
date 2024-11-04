#include "Camera.h"
#include <iostream>
#include "Constants.h"

Camera::Camera(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
    cameraRect = { 0, 0, screenWidth, screenHeight };
}

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}

void Camera::update(const SDL_Rect& playerRect, int levelWidth, int levelHeight) {
    // ��������� ������� ��������� ������
    int targetX = playerRect.x + playerRect.w / 2 - SCREEN_WIDTH / 2;
    int targetY = playerRect.y + playerRect.h / 2 - SCREEN_HEIGHT / 2 - 200.0;

    // ��������� �������� ������������ ��� �������� �����������
    cameraRect.x = static_cast<int>(lerp(cameraRect.x, targetX, 0.1f));  // 0.1f � �������� ����������� (��� ����� � 1.0, ��� �������)
    cameraRect.y = static_cast<int>(lerp(cameraRect.y, targetY, 0.1f));


    // ������������� ������� ������
    /*if (cameraRect.x < 0) {
        cameraRect.x = 0;
    }
    if (cameraRect.y < 0) {
        cameraRect.y = 0;
    }
    if (cameraRect.x + screenWidth > levelWidth) {
        cameraRect.x = levelWidth - screenWidth;
    }
    if (cameraRect.y + screenHeight > levelHeight) {
        cameraRect.y = levelHeight - screenHeight;
    }
    std::cout << "Camera X: " << cameraRect.x << ", Camera Y: " << cameraRect.y << std::endl;
    */
}
