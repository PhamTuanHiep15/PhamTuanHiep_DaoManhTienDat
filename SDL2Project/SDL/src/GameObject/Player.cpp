#include "player.h"
#include "Define.h"
#include "ResourceManagers.h"

Player::Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime) {
    
}

void Player::updatePosition(float deltaX, float deltaY) {

}
void Player::PlayerMoveRight(float deltaTime)
{
    m_position.x += playerSpeed * deltaTime;
}
void Player::PlayerMoveLeft(float deltaTime)
{
    m_position.x -= playerSpeed * deltaTime;
}
void Player::PlayerMoveUp(float deltaTime)
{
    m_position.y -= playerSpeed * deltaTime;
}
void Player::PlayerMoveDown(float deltaTime)
{
    m_position.y += playerSpeed * deltaTime;
}
SDL_Rect Player::GetRect() {
    SDL_Rect rect;
    rect.x = m_position.x;
    rect.y = m_position.y;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;
    return rect;
}