#include "enemy.h"

Enemy::Enemy(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, int enemyDamage, int enemySpeed)
    : Entity(pos, anim), damage(enemyDamage), speed(enemySpeed) {}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::setDamage(int enemyDamage) {
    damage = enemyDamage;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::setSpeed(int enemySpeed) {
    speed = enemySpeed;
}

void Enemy::moveLeft() {
    position.x -= speed;
}

void Enemy::moveRight() {
    position.x += speed;
}
