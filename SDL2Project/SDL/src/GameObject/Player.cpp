#include "player.h"
#include "Define.h"

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime) {
    
}

void Player::updatePosition(float deltaX, float deltaY) {

}
void Player::PlayerMoveRight(float deltaTime)
{
    m_position.x += PLAYER_SPEED * deltaTime;
}
void Player::PlayerMoveLeft(float deltaTime)
{
    m_position.x -= PLAYER_SPEED * deltaTime;
}