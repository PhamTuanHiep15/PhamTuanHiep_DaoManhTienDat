#include "Player.h"
#include "Define.h"
#include "ResourceManagers.h"
#include "Collision.h"

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
            SetTexture(ResourceManagers::GetInstance()->GetTexture("fireboy_run_left.png"));
        }
        else if (keyPress & (1 << 2)) {
            PlayerMoveRight(deltaTime);
            SetTexture(ResourceManagers::GetInstance()->GetTexture("fireboy_run_right.png"));
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
            SetTexture(ResourceManagers::GetInstance()->GetTexture("fireboy_jump.png"));
        }
    } else if (m_velocityY > 0 ) SetTexture(ResourceManagers::GetInstance()->GetTexture("fireboy_fall.png"));
   
    else SetTexture(ResourceManagers::GetInstance()->GetTexture("fireboy_idle.png"));

    SDL_Rect previousRect = GetRect();
    if (Collision::GetInstance()->MapCollision(GetRect())) {
        m_position.x = previousRect.x;
        m_position.y = previousRect.y;
    }
}
void Player::PlayerBar() {
    //manaBar
    manaBar.x = 10;
    manaBar.y = 10;
    manaBar.w = 20*jumpCount;
    manaBar.h = 10;
    
    //hpBar
    hpBar.x = 10;
    hpBar.y = 30;
    hpBar.w = 300;
    hpBar.h = 20;
}

void Player::Update(float deltatime) {
    m_currentTicks += deltatime;
    if (m_currentTicks >= m_frameTime) {
        m_currentFrame++;
        if (m_currentFrame >= m_frameCount) {
            m_currentFrame = 0;
        }
        m_currentTicks -= m_frameTime;
    }
    //gravity
    m_velocityY += GRAVITY * deltatime;

    if (m_position.y + TILE_SIZE >= SCREEN_HEIDHT - TILE_SIZE) {
        m_velocityY = 0;
        m_position.y = SCREEN_HEIDHT - TILE_SIZE - TILE_SIZE;
    }
    else {
        m_position.y += m_velocityY * deltatime;
    }
    m_Rect = GetRect();
}