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
}
void Player::PlayerJump() {
    m_position.y -= 1;  
    if (canJump) {
        m_velocityY = -jumpSpeed;
        jumpCount--;
    }
    if (jumpCount == 0) canJump = false;
    else canJump = true;

};

void Player::HandleInput(int keyPress, float deltaTime) {
    if (keyPress & 1) {
        PlayerMoveLeft(deltaTime);
        SetTexture(ResourceManagers::GetInstance()->GetTexture("left.png"));
    }
    else if (keyPress & (1 << 2)) {
        PlayerMoveRight(deltaTime);
        SetTexture(ResourceManagers::GetInstance()->GetTexture("right.png"));
    }
    else if (keyPress & (1 << 1)) {
        PlayerMoveDown(deltaTime);
        SetTexture(ResourceManagers::GetInstance()->GetTexture("down.png"));
    }
    else if (keyPress & (1 << 3)) {
        PlayerMoveUp(deltaTime);
        SetTexture(ResourceManagers::GetInstance()->GetTexture("up.png"));
    }
    else if (keyPress & (1 << 4)) {
        PlayerJump();
        SetTexture(ResourceManagers::GetInstance()->GetTexture("up.png"));
    }
}