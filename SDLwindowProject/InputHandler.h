#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <iostream>

class InputHandler {
public:
    static InputHandler& getInstance() {
        static InputHandler instance;
        return instance;
    }

    void update();
    bool isQuit() const { return quit; }

private:
    InputHandler() : quit(false) {}
    bool quit;
};

#endif
