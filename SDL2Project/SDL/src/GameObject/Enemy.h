
#pragma once

#include "SpriteAnimation.h" 

enum class EnemyType {
    SNAKE,
    DINO,
    SLIME
};

enum class Direction {
    LEFT,
    RIGHT
};

class Enemy : public SpriteAnimation {
public:
    Enemy(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);
    ~Enemy();

    void updatePosition(float deltaX, float deltaY);
    void Update(float deltatime) override;
    void enemyMove1(float deltatime);
    void SetEnemyType(EnemyType type) { m_type = type; }
    void SetDirection(Direction direction) { m_direction = direction; }
private:
    EnemyType m_type;
    Direction m_direction;
    int m_steps;
};
