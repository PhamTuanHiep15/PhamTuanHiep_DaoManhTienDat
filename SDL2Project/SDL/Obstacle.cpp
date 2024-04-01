#include "Obstacle.h"
#include <CMath.h>

Obstacle::Obstacle(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, bool isDestructible)
    : Entity(pos, anim), destructible(isDestructible) {}

bool Obstacle::isDestructible() const {
    return destructible;
}

void Obstacle::setDestructible(bool isDestructible) {
    destructible = isDestructible;
}
