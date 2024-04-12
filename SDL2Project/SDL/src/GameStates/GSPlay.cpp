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

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_soundEffectOnClick = std::make_shared<Sound>();
	m_soundEffectOnClick->LoadSound("Data/Sounds/click.wav");

	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");

    //backgrond
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_GSPlay.png");
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

    //ground
    auto groundTexture = ResourceManagers::GetInstance()->GetTexture("ground.png");
    m_ground = std::make_shared<Sprite2D>(groundTexture, SDL_FLIP_NONE);
    m_ground->SetSize(SCREEN_WIDTH, TILE_SIZE); 
    m_ground->Set2DPosition(0, SCREEN_HEIDHT - TILE_SIZE);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH-10-button->GetWidth(), 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


    //player
    texture = ResourceManagers::GetInstance()->GetTexture("down.png");
    m_player = std::make_shared<Player>(texture, 1, 9, 1, 0.2f);
    m_player->SetFlip(SDL_FLIP_HORIZONTAL);
    m_player->SetSize(TILE_SIZE, TILE_SIZE);
    m_player->Set2DPosition(80, 310);
    //Camera::GetInstance()->SetTarget(obj);
    m_listPlayer.push_back(m_player);

    m_KeyPress = 0;


	//enemy
	texture = ResourceManagers::GetInstance()->GetTexture("sneakLeft.png");
	m_enemy = std::make_shared<Enemy>(texture, 1, 4, 1, 0.2f);
    m_enemy->SetFlip(SDL_FLIP_HORIZONTAL);
    m_enemy->SetSize(70, 30);
    m_enemy->Set2DPosition(360, 380);
	//Camera::GetInstance()->SetTarget(obj);
	m_listEnemyAnimation.push_back(m_enemy);

    //item
    texture = ResourceManagers::GetInstance()->GetTexture("chest.png");
    m_item = std::make_shared<Item>(texture, 1, 1, 1, 0.2f);
    m_item->SetFlip(SDL_FLIP_HORIZONTAL);
    m_item->SetSize(TILE_SIZE, TILE_SIZE);
    m_item->Set2DPosition(200, 200);
    //Camera::GetInstance()->SetTarget(obj);
    m_listItemAnimation.push_back(m_item);
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}
void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN )//&& e.key.repeat == 0) //For e.key.repeat it's because key repeat is enabled by default and if you press and hold a key it will report multiple key presses. That means we have to check if the key press is the first one because we only care when the key was first pressed.
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)                                                                                            
		{                                                                                                                     
		case SDLK_LEFT:
			m_KeyPress |= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress |= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress |= 1 << 3;
			break;
        case SDLK_SPACE:
            m_KeyPress |= 1 << 4;
            break;
		default:
			break;
		}
	}
	////Key Up
	else if (e.type == SDL_KEYUP )//&& e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_KeyPress ^= 1;
			break;
		case SDLK_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case SDLK_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case SDLK_UP:
			m_KeyPress ^= 1 << 3;
			break;
        case SDLK_SPACE:
            m_KeyPress ^= 1 << 4;
            break;
		default:
			break;
		}
	}
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
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	for (auto it : m_listPlayer)
	{
       

        if (m_KeyPress & 1)
        {
            it->PlayerMoveLeft(deltaTime);
            it->SetTexture(ResourceManagers::GetInstance()->GetTexture("left.png"));
        }
        else if (m_KeyPress & (1 << 2))
        {
            it->PlayerMoveRight(deltaTime);
            it->SetTexture(ResourceManagers::GetInstance()->GetTexture("right.png"));
        }
        else if (m_KeyPress & (1 << 1))
        {
            it->PlayerMoveDown(deltaTime);
            it->SetTexture(ResourceManagers::GetInstance()->GetTexture("down.png"));
        }
        else if (m_KeyPress & (1 << 3))
        {
            it->PlayerMoveUp(deltaTime);
            it->SetTexture(ResourceManagers::GetInstance()->GetTexture("up.png"));
        }
        else if (m_KeyPress & (1 << 4))
        {
            it->PlayerJump();
            it->SetTexture(ResourceManagers::GetInstance()->GetTexture("up.png"));
        }

        SDL_Rect playerRect = it->GetRect();
        for (auto it : m_listItemAnimation)
        {
            SDL_Rect itemRect = it->GetRect();

            bool col = Collision::CheckCollision(playerRect, itemRect);
            if (col) printf("collision");
        }

        int num = it->jumpCount;

        printf("%d %d %d\n", playerRect.x, playerRect.y, num);
 
		it->Update(deltaTime);

      

	}
	//sneak move

	for (auto it : m_listEnemyAnimation)
	{
		it->Update(deltaTime);
	}

    for (auto it : m_listItemAnimation)
    {
        it->Update(deltaTime);
    }
	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	m_enemy->Update(deltaTime);
}


void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
    m_ground->Draw(renderer);
	//m_score->Draw();
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

    
	
}