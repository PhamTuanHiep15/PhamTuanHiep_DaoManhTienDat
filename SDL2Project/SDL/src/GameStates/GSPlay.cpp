#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Item.h"
#include "Collision.h"
#include <random>
#include "MapParser.h"
#include <iostream>

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}

void GSPlay::Init()
{
    //Set Font
    m_textColor = { 0, 0, 255 };
    m_textItem = std::make_shared<Text>("Data/gamera.ttf", m_textColor);
    m_textItem->SetSize(200, 40);
    m_textItem->Set2DPosition(700, 20);
    std::string itemText = "item: " + std::to_string(n_Item) + "/5";
    m_textItem->LoadFromRenderText(itemText.c_str());

    m_textColor = { 255, 255, 255 };
    m_GameOver = std::make_shared<Text>("Data/gamera.ttf", m_textColor);
    m_GameOver->SetSize(450, 75);
    m_GameOver->Set2DPosition((SCREEN_WIDTH - m_GameOver->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 180);
    std::string itemText1 = "";
    m_GameOver->LoadFromRenderText(itemText1.c_str());

    m_soundEffectOnClick = std::make_shared<Sound>();
    m_soundEffectOnClick->LoadSound("Data/Sounds/click.wav");

    //auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");


    //background
    auto texture = ResourceManagers::GetInstance()->GetTexture("bg_GSPlay.png");
    m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
    m_background->SetSize(MAP_WIDTH, MAP_HEIDTH);
    m_background->Set2DPosition(0, 0);

    //ground
    auto groundTexture = ResourceManagers::GetInstance()->GetTexture("ground.png");
    m_ground = std::make_shared<Sprite2D>(groundTexture, SDL_FLIP_NONE);
    m_ground->SetSize(SCREEN_WIDTH * 4, TILE_SIZE);
    m_ground->Set2DPosition(0, SCREEN_HEIDHT - TILE_SIZE);

    //map
    if (MapParser::GetInstance()->Load()) {
        std::cout << "Failed to load map......." << std::endl;
    }
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");


    // button close
    texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
    button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    button->SetSize(50, 50);
    button->Set2DPosition(SCREEN_WIDTH - 10 - button->GetWidth(), 10);
    button->SetOnClick([this]() {
        GameStateMachine::GetInstance()->PopState();
        });
    m_listButton.push_back(button);


    //player
    texture = ResourceManagers::GetInstance()->GetTexture("girl_idle.png");
    m_player = std::make_shared<Player>(texture, 1, 11, 1, 0.2f);
    m_player->SetFlip(SDL_FLIP_HORIZONTAL);
    m_player->SetSize(TILE_SIZE * 1.25, TILE_SIZE * 1.25);
    m_player->Set2DPosition(20,/* SCREEN_HEIDHT - TILE_SIZE * 2*/ 250);
    Camera::GetInstance()->SetTarget(m_player);
    m_listPlayer.push_back(m_player);

    m_KeyPress = 0;


    //enemy
    texture = ResourceManagers::GetInstance()->GetTexture("dino.png");
    dino = std::make_shared<Enemy>(texture, 1, 6, 1, 0.2f);
    dino->SetSize(30, 30);
    dino->Set2DPosition(1120, 69.5);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(dino);

    texture = ResourceManagers::GetInstance()->GetTexture("dino.png");
    dino1 = std::make_shared<Enemy>(texture, 1, 6, 1, 0.2f);
    dino1->SetSize(30, 30);
    dino1->SetFlip(SDL_FLIP_HORIZONTAL);
    dino1->Set2DPosition(2800, 452.5);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(dino1);

    texture = ResourceManagers::GetInstance()->GetTexture("snake_left.png");
    snake = std::make_shared<Enemy>(texture, 1, 4, 1, 0.2f);
    snake->SetSize(30, 18);
    snake->Set2DPosition(445, 205);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(snake);

    texture = ResourceManagers::GetInstance()->GetTexture("snake_right.png");
    snake1 = std::make_shared<Enemy>(texture, 1, 4, 1, 0.2f);
    snake1->SetSize(30, 18);
    snake1->Set2DPosition(2480, 205);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(snake1);

    texture = ResourceManagers::GetInstance()->GetTexture("snake_left.png");
    snake2 = std::make_shared<Enemy>(texture, 1, 4, 1, 0.2f);
    snake2->SetSize(30, 18);
    snake2->Set2DPosition(2750, 205);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(snake2);

    texture = ResourceManagers::GetInstance()->GetTexture("slime.png");
    slime = std::make_shared<Enemy>(texture, 1, 5, 1, 0.2f);
    slime->SetSize(40, 40);
    slime->Set2DPosition(1002, 380);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(slime);

    texture = ResourceManagers::GetInstance()->GetTexture("slime.png");
    slime1 = std::make_shared<Enemy>(texture, 1, 5, 1, 0.2f);
    slime1->SetSize(40, 40);
    slime1->Set2DPosition(1850, 410);
    //Camera::GetInstance()->SetTarget(obj);
    m_listEnemyAnimation.push_back(slime1);

    //item
    texture = ResourceManagers::GetInstance()->GetTexture("chest.png");
    chest = std::make_shared<Item>(texture, 1, 1, 1, 0.2f);
    chest->SetSize(TILE_SIZE, TILE_SIZE);
    chest->Set2DPosition(65, 191);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(chest);

    texture = ResourceManagers::GetInstance()->GetTexture("book.png");
    book = std::make_shared<Item>(texture, 1, 6, 7, 0.3f);
    book->SetSize(TILE_SIZE, TILE_SIZE);
    book->Set2DPosition(1190, 66.5);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(book);

    texture = ResourceManagers::GetInstance()->GetTexture("coin.png");
    coin = std::make_shared<Item>(texture, 1, 15, 1, 0.2f);
    coin->SetSize(TILE_SIZE, TILE_SIZE);
    coin->Set2DPosition(550, 360);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(coin);

    texture = ResourceManagers::GetInstance()->GetTexture("coin.png");
    coin1 = std::make_shared<Item>(texture, 1, 15, 1, 0.2f);
    coin1->SetSize(TILE_SIZE, TILE_SIZE);
    coin1->Set2DPosition(1980, 150);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(coin1);

    texture = ResourceManagers::GetInstance()->GetTexture("coin.png");
    coin2 = std::make_shared<Item>(texture, 1, 15, 1, 0.2f);
    coin2->SetSize(TILE_SIZE, TILE_SIZE);
    coin2->Set2DPosition(2580, 280);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(coin2);

    s_Instance = this;
}

GSPlay* GSPlay::s_Instance = nullptr;

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}
void GSPlay::Resume()
{

}



void GSPlay::HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        HandleKeyEvents(e);
        HandleTouchEvents(e);
    }
}

void GSPlay::HandleKeyEvents(SDL_Event& e) {
    InputHandler::HandleKeyEvents(e, m_KeyPress);
}


void GSPlay::HandleTouchEvents(SDL_Event& e)
{
    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            m_soundEffectOnClick->PlaySfx(0);
            break;
        }
    }
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}


void GSPlay::Update(float deltaTime)
{
    m_LevelMap->Update();

    for (auto it : m_listButton)
    {
        it->Update(deltaTime);
    }

    if (gameRunning) {
        for (auto player : m_listPlayer)
        {

            player->HandleInput(m_KeyPress, deltaTime);
            player->PlayerBar();

            SDL_Rect playerRect = player->GetRect();
            for (auto it : m_listItemAnimation)
            {
                SDL_Rect itemRect = it->GetRect();

                bool col = Collision::CheckCollision(playerRect, itemRect);
                if (col) {
                    printf("collision ");
                    it->Set2DPosition(-100, -100);
                    n_Item++;
                    printf("%d\n", n_Item);
                    std::string itemText = "item: " + std::to_string(n_Item) + "/5";
                    m_textItem->LoadFromRenderText(itemText.c_str());
                    if (n_Item ==5 ) { gameRunning = false;
                    std::string itemText1 = "You Win ";
                    m_GameOver->LoadFromRenderText(itemText1.c_str());}
                       

                }
            }
            for (auto it : m_listEnemyAnimation)
            {
                SDL_Rect itemRect = it->GetRect();

                bool col = Collision::CheckCollision(playerRect, itemRect);
                if (col) {
                    printf("collision ");
                    std::string itemText1 = "Game Over ";
                    m_GameOver->LoadFromRenderText(itemText1.c_str());
                    gameRunning = false;
                    break;

                }
            }

            if (playerRect.y == SCREEN_HEIDHT - 2 * TILE_SIZE && player->jumpCount < 20) player->jumpCount++;
            int num = player->jumpCount;
            StaminaBar = player->manaBar;


            printf("%d %d %d\n", playerRect.x, playerRect.y, num);

            player->Update(deltaTime);
        }
        //enemy
        for (auto it : m_listEnemyAnimation)
        {
            it->enemyMove(deltaTime);
            it->Update(deltaTime);
        }

        for (auto it : m_listItemAnimation)
        {
            it->Update(deltaTime);
        }
        //Update position of camera
        Camera::GetInstance()->Update(deltaTime);
        dino->Update(deltaTime);
        snake->Update(deltaTime);
        snake1->Update(deltaTime);
        snake2->Update(deltaTime);
        slime->Update(deltaTime);

        Collision::GetInstance()->Update();
    }
}


void GSPlay::Draw(SDL_Renderer* renderer)
{
    m_background->Draw(renderer);

    //m_score->Draw();
    m_LevelMap->Render();

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &StaminaBar);

    for (auto it : m_listButton)
    {
        it->Draw(renderer);
    }
    //  player
    for (auto it : m_listPlayer)
    {
        it->Draw(renderer);
    }



    for (auto it : m_listEnemyAnimation)
    {
        it->Draw(renderer);
    }

    for (auto it : m_listItemAnimation)
    {
        it->Draw(renderer);
    }
    m_textItem->Draw(renderer);
    m_GameOver->Draw(renderer);

}