#include "player.h"

Player::Player(Vector2 pos, std::shared_ptr<SpriteAnimation> anim, int playerLevel, int playerHealth)
    : Entity(pos, anim), level(playerLevel), healthBar(playerHealth) {}

int Player::getLevel() const {
    return level;
}

void Player::setLevel(int playerLevel) {
    level = playerLevel;
}

int Player::getHealthBar() const {
    return healthBar;
}

void Player::setHealthBar(int playerHealth) {
    healthBar = playerHealth;
}

void Player::moveHealthBar(int dx) {
    healthBar += dx;
    // update HP_Bar here
}

void Player::moveLevelBar(int dx) {
    level += dx;
    // update LV_Bar here
}
