#include "Enemy.h"
#include "Define.h"
#include "ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime) {

}

void Enemy::updatePosition(float deltaX, float deltaY) {

}

void Enemy::enemyMove1(float deltatime) {
    /*int n = 0;
    if (n < 50) {
        m_position.x += PLAYER_SPEED_DEFAULT;
        SetTexture(ResourceManagers::GetInstance()->GetTexture("dino.png"));
        n++;
    }
    else if (n < 100) {
        m_position.x -= PLAYER_SPEED_DEFAULT;
        SetTexture(ResourceManagers::GetInstance()->GetTexture("dino.png"));
        n++;
    }
    else n = 0;*/

    m_position.x += PLAYER_SPEED_DEFAULT;
    
}

void Enemy::Update(float deltatime) {
    m_currentTicks += deltatime;
    if (m_currentTicks >= m_frameTime) {
        m_currentFrame++;
        if (m_currentFrame >= m_frameCount) {
            m_currentFrame = 0;
        }
        m_currentTicks -= m_frameTime;
    }

}