#pragma once

#include "SpriteAnimation.h" 

class Player : public SpriteAnimation {
public:
    Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);


    void updatePosition(float deltaX, float deltaY);

   
    void PlayerMoveLeft(float deltaTime);
    void PlayerMoveRight(float deltaTime);

    int playerSpeed = PLAYER_SPEED_DEFAULT;
};
