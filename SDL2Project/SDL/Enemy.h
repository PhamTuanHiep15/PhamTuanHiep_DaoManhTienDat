#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
private:
    int damage; // 
    int speed; // 

public:
    Enemy(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, int enemyDamage, int enemySpeed);


    int getDamage() const;
    void setDamage(int enemyDamage);

    int getSpeed() const;
    void setSpeed(int enemySpeed);


    void moveLeft();
    void moveRight();
};

#endif // ENEMY_H
