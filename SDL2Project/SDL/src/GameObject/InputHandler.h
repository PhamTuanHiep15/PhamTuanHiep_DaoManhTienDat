#pragma once
#include <SDL.h>

class InputHandler {
public:
    static void HandleKeyEvents(SDL_Event& e, int& keyPress);
    static void HandleTouchEvents(SDL_Event& e);
};