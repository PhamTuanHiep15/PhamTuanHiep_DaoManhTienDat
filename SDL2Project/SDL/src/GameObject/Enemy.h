
#pragma once

#include "SpriteAnimation.h" 

class Enemy : public SpriteAnimation {
public:
    Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);


    void updatePosition(float deltaX, float deltaY);


};
