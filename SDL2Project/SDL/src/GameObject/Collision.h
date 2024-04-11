#pragma once
#include <SDL_rect.h>

class Collision {
public:
    static bool CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};