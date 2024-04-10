#include "Enemy.h"
#include "Define.h"
#include "ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime) {

}

void Enemy::updatePosition(float deltaX, float deltaY) {

}