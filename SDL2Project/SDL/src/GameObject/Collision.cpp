#include "collision.h"

bool Collision::CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
   
    if (rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y) {
        return true; 
    }
    return false; 
}

void Collision::Update() {
}