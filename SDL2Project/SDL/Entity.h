#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include "SpriteAnimation.h"

class Entity {
protected:
    Vector2 position; //
    std::shared_ptr<SpriteAnimation> animation; //

public:
    Entity(Vector2 pos, std::shared_ptr<SpriteAnimation> anim);

    // Getter and setter 
    Vector2 getPosition() const;
    void setPosition(Vector2 pos);

    std::shared_ptr<SpriteAnimation> getAnimation() const;
    void setAnimation(std::shared_ptr<SpriteAnimation> anim);

    // 
    void move(int dx, int dy);
};

#endif // ENTITY_H
