#pragma once
#include <SDL_rect.h>
#include "Player.h"
#include "Item.h"
#include "GSPlay.h"
class Collision {
public:
    static bool CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
    void Update();
};