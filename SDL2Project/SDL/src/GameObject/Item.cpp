#include "Item.h"
#include "Define.h"
#include "ResourceManagers.h"

Item::Item(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime) {

}

void Item::updatePosition(float deltaX, float deltaY) {

}