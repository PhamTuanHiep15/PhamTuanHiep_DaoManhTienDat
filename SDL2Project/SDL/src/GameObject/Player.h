#pragma once

#include "SpriteAnimation.h" 

class Player : public SpriteAnimation {
public:
    Player(std::shared_ptr<TextureManager> texture, int spriteRow, int frameCount, int numAction, float frameTime);


    void updatePosition(float deltaX, float deltaY);

   
    void PlayerMoveLeft(float deltaTime);
    void PlayerMoveRight(float deltaTime);
    void PlayerMoveUp(float deltaTime);
    void PlayerMoveDown(float deltaTime);
    void PlayerJump();

    int playerSpeed = PLAYER_SPEED_DEFAULT;

    int jumpSpeed = 300;
    int jumpCount = STAMINA;
    bool canJump = true;

};
