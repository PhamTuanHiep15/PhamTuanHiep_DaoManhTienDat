#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "entity.h"

class Obstacle : public Entity {
private:
    bool destructible; 

public:
    Obstacle(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, bool isDestructible);

    
    bool isDestructible() const;
    void setDestructible(bool isDestructible);
};

#endif // OBSTACLE_H
