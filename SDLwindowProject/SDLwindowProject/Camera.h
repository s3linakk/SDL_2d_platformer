#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>

class Camera {
public:
    SDL_Rect cameraRect;

    Camera(int screenWidth, int screenHeight);
    void update(const SDL_Rect& playerRect, int levelWidth, int levelHeight);

private:
    int screenWidth;
    int screenHeight;
};

#endif
