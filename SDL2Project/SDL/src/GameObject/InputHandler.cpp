// InputHandler.cpp
#include "InputHandler.h"

void InputHandler::HandleKeyEvents(SDL_Event& e, int& keyPress) {
    //If a key was pressed
    if (e.type == SDL_KEYDOWN) {
        // Adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            keyPress |= 1;
            break;
        case SDLK_DOWN:
            keyPress |= 1 << 1;
            break;
        case SDLK_RIGHT:
            keyPress |= 1 << 2;
            break;
        case SDLK_UP:
            keyPress |= 1 << 3;
            break;
        case SDLK_SPACE:
            keyPress |= 1 << 4;
            break;
        default:
            break;
        }
    }
    // Key Up
    else if (e.type == SDL_KEYUP) {
        // Adjust the velocity
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            keyPress ^= 1;
            break;
        case SDLK_DOWN:
            keyPress ^= 1 << 1;
            break;
        case SDLK_RIGHT:
            keyPress ^= 1 << 2;
            break;
        case SDLK_UP:
            keyPress ^= 1 << 3;
            break;
        case SDLK_SPACE:
            keyPress ^= 1 << 4;
            break;
        default:
            break;
        }
    }
}

void InputHandler::HandleTouchEvents(SDL_Event& e) {
    // Handle touch events
}
