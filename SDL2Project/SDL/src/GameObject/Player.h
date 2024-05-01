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
    SDL_Rect GetRect();
    void HandleInput(int keyPress, float deltaTime);
    void PlayerBar();
    void Update(float deltatime) override;



    int playerSpeed = PLAYER_SPEED_DEFAULT;
    int jumpSpeed = 300;
    int jumpCount = STAMINA;
    int lv = 1;
    int hp = 200 + HP_DEFAULT * lv / 2;
    bool canJump = true;
    SDL_Rect manaBar;
    SDL_Rect hpBar;
    SDL_Rect m_Rect;
};
