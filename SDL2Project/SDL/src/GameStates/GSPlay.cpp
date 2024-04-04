#include "GSPlay.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
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
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play.jpg");

	// background
	
	m_background = std::make_shared<Sprite2D>( texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>( texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH-10-button->GetWidth(), 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

   // Animation 
	texture = ResourceManagers::GetInstance()->GetTexture("_Idle.png");
	obj = std::make_shared<SpriteAnimation>( texture, 1, 10, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(125, 100);
	obj->Set2DPosition(80, 310);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	m_KeyPress = 0;
	
	m_musicBackground = std::make_shared<Sound>();
	m_musicBackground->LoadSound("Data/Sounds/Play.wav");
	m_musicBackground->PlaySound();

	//item
	texture = ResourceManagers::GetInstance()->GetTexture("sneakLeft.png");
	obj = std::make_shared<SpriteAnimation>(texture, 1, 4, 1, 0.2f);
	obj->SetFlip(SDL_FLIP_HORIZONTAL);
	obj->SetSize(70, 30);
	obj->Set2DPosition(360, 380);
	//Camera::GetInstance()->SetTarget(obj);
	m_listObjAnimation.push_back(obj);
}

void GSPlay::Exit()
{
	m_musicBackground->StopSound();
}


void GSPlay::Pause()
{
	m_musicBackground->PauseSound();
}
void GSPlay::Resume()
{
	m_musicBackground->PlaySound();
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

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

	for (auto it : m_listAnimation)
	{
		if (m_KeyPress & 1) 
		{
			it->MoveLeft(deltaTime);
			it->SetTexture(ResourceManagers::GetInstance()->GetTexture("_RunLeft.png")); 
		}
		else if (m_KeyPress & (1 << 2)) 
		{
			it->MoveRight(deltaTime);
			it->SetTexture(ResourceManagers::GetInstance()->GetTexture("_RunRight.png"));
		}
		else if (m_KeyPress & (1 << 1))
		{
			it->SetTexture(ResourceManagers::GetInstance()->GetTexture("_Attack.png"));
		}
		else it->SetTexture(ResourceManagers::GetInstance()->GetTexture("_Idle.png"));

		it->Update(deltaTime);

	}
	//sneak move
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1000);
	bool isMovingLeft = true;

	for (auto it : m_listObjAnimation)
	{
		int randomNumber = dis(gen);
		if (randomNumber > 900)
		{
			if (isMovingLeft)
			{
				it->MoveRight(deltaTime);
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("sneakRight.png"));
				printf("%d\n", randomNumber);
			}
			else
			{
				it->MoveLeft(deltaTime);
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("sneakLeft.png"));
				printf("%d\n", randomNumber);
			}
			bool isMovingLeft = true;
		}
		it->Update(deltaTime);
	}

	//Update position of camera
	Camera::GetInstance()->Update(deltaTime);
	obj->Update(deltaTime);
}

void GSPlay::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	//m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}
//	obj->Draw(renderer);
	for (auto it : m_listAnimation)
	{
		it->Draw(renderer);
	}
	for (auto it : m_listObjAnimation)
	{
		it->Draw(renderer);
	}
	
}