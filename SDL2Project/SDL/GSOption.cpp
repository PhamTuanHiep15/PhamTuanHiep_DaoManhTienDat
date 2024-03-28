#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSOption::GSOption()
{
}


GSOption::~GSOption()
{
}


void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background

	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 50, 10);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//music game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	std::shared_ptr<MouseButton> btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->SetSize(100, 100);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIDHT / 2 -170);
	m_listButton.push_back(btnOption);
	
	//sfx game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	btnOption = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnOption->Set2DPosition((SCREEN_WIDTH - btnOption->GetWidth()) / 2, SCREEN_HEIDHT / 2 );
	btnOption->SetSize(100, 100);
	m_listButton.push_back(btnOption);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	m_KeyPress = 0;

}

void GSOption::Exit()
{
}


void GSOption::Pause()
{

}
void GSOption::Resume()
{
	// button close
	//auto texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	//button->SetTexture(texture);

}


void GSOption::HandleEvents()
{
}

void GSOption::HandleKeyEvents(SDL_Event& e)
{
}

void GSOption::HandleTouchEvents(SDL_Event& e)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvent(&e))
		{
			break;
		}
	}
}

void GSOption::HandleMouseMoveEvents(int x, int y)
{
}

void GSOption::Update(float deltaTime)
{

	// Key State event

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

}

void GSOption::Draw(SDL_Renderer* renderer)
{
	m_background->Draw(renderer);
	for (auto it : m_listButton)
	{
		it->Draw(renderer);
	}

}
