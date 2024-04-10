
#pragma once

#include "SpriteAnimation.h" 

class Item : public SpriteAnimation {
public:
    Item(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);
    void updatePosition(float deltaX, float deltaY);

};
