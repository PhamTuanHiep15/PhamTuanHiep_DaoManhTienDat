#include "entity.h"

Entity::Entity(Vector2 pos, std::shared_ptr<SpriteAnimation> anim) : position(pos), animation(anim) {}

Vector2 Entity::getPosition() const {
    return position;
}

void Entity::setPosition(Vector2 pos) {
    position = pos;
}

std::shared_ptr<SpriteAnimation> Entity::getAnimation() const {
    return animation;
}

void Entity::setAnimation(std::shared_ptr<SpriteAnimation> anim) {
    animation = anim;
}

void Entity::move(int dx, int dy) {
    position.x += dx;
    position.y += dy;
}
