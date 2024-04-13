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

SDL_Rect Player::GetRect() {
    SDL_Rect rect;
    rect.x = m_position.x+TILE_SIZE/3;
    rect.y = m_position.y;
    rect.w = TILE_SIZE/3;
    rect.h = TILE_SIZE;
    return rect;
}


void Player::HandleInput(int keyPress, float deltaTime) {

    if (keyPress & 1 || keyPress & (1 << 2) || keyPress & (1 << 4) ) {
        if (keyPress & 1) {
            PlayerMoveLeft(deltaTime);
            SetTexture(ResourceManagers::GetInstance()->GetTexture("girl_run_left.png"));
        }
        else if (keyPress & (1 << 2)) {
            PlayerMoveRight(deltaTime);
            SetTexture(ResourceManagers::GetInstance()->GetTexture("girl_run_right.png"));
        }

        /*
        *  else if (keyPress & (1 << 1)) {
            PlayerMoveDown(deltaTime);
            SetTexture(ResourceManagers::GetInstance()->GetTexture("down.png"));
        }
        else if (keyPress & (1 << 3)) {
            PlayerMoveUp(deltaTime);
            SetTexture(ResourceManagers::GetInstance()->GetTexture("up.png"));
        }
        */

        else if (keyPress & (1 << 4)) {
            PlayerJump();
            SetTexture(ResourceManagers::GetInstance()->GetTexture("girl_jump.png"));
        }
    } else if (m_velocityY > 0 ) SetTexture(ResourceManagers::GetInstance()->GetTexture("girl_falling.png"));
   
    else SetTexture(ResourceManagers::GetInstance()->GetTexture("girl_idle.png"));
}
void Player::PlayerBar() {
    //manaBar
    manaBar.x = 10;
    manaBar.y = 10;
    manaBar.w = 2*jumpCount;
    manaBar.h = 10;
    
    //hpBar
    hpBar.x = 10;
    hpBar.y = 30;
    hpBar.w = 300;
    hpBar.h = 20;



}
