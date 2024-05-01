#include "Enemy.h"
#include "Define.h"
#include "ResourceManagers.h"

Enemy::Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime)
    : SpriteAnimation(texture, spriteRow, frameCount, numAction, frameTime), m_type(EnemyType::SNAKE), m_direction(Direction::RIGHT), m_steps(0) 
{
}

Enemy::~Enemy()
{
}

void Enemy::updatePosition(float deltaX, float deltaY) {
}

void Enemy::enemyMove1(float deltatime) {
    if (m_type == EnemyType::SNAKE) {
        // Di chuyển snake 3 ô rồi quay lại
        if (m_direction == Direction::RIGHT) {
            m_position.x += enemy_speed;
            m_steps++;
            if (m_steps >= 150) {
                m_direction = Direction::LEFT;
                SetFlip(SDL_FLIP_NONE);
                m_steps = 0;
            }
        }
        else {
            
            m_position.x -= enemy_speed;
            m_steps++;
            if (m_steps >= 150) {
                m_direction = Direction::RIGHT;
                SetFlip(SDL_FLIP_HORIZONTAL);
                m_steps = 0;
            }
        }
    }
    else if (m_type == EnemyType::DINO) {
        // Di chuyển dino 10 ô rồi quay lại
        if (m_direction == Direction::RIGHT) {
            m_position.x += enemy_speed;
            m_steps++;
            if (m_steps >= 280) {
                m_direction = Direction::LEFT;
                SetFlip(SDL_FLIP_HORIZONTAL);
                m_steps = 0;
            }
        }
        else {
            m_position.x -= enemy_speed;
            m_steps++;
            if (m_steps >= 280) {
                m_direction = Direction::RIGHT;
                SetFlip(SDL_FLIP_NONE);
                m_steps = 0;
            }
        }
    }
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