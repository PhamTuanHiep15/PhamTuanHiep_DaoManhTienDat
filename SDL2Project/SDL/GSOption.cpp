#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSOption::GSOption() : m_soundEffectClick(std::make_shared<Sound>()), m_musicBackground(std::make_shared<Sound>())
{
	m_soundEffectClick->LoadSfx("Data/Sounds/click.wav");
}


GSOption::~GSOption()
{
}


void GSOption::Init()
{
	//auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.png");

	// background
	m_background = std::make_shared<Sprite2D>(texture, SDL_FLIP_NONE);
	m_background->SetSize(SCREEN_WIDTH, SCREEN_HEIDHT);
	m_background->Set2DPosition(0, 0);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.png");
	button = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	button->SetSize(50, 50);
	button->Set2DPosition(SCREEN_WIDTH - 10 - button->GetWidth(), 10);
	button->SetOnClick([this]() {
		m_soundEffectClick->PlaySfx(0);
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// Button Music
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->SetSize(100, 100);
	btnMusic->Set2DPosition((SCREEN_WIDTH - btnMusic->GetWidth()) / 2, SCREEN_HEIDHT / 2 -170);
	btnMusic->SetOnClick([this]() {
		m_soundEffectClick->PlaySfx(0);
		m_isMusicOn = !m_isMusicOn; // Đảo ngược trạng thái âm nhạc
		if (m_isMusicOn) {
			m_musicBackground->PlaySound();
			btnMusic->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_on.tga"));
		}
		else {
			m_musicBackground->PauseSound();
			btnMusic->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga"));
		}
		});
	m_listButton.push_back(btnMusic);

	// Nhạc nền
		m_musicBackground->LoadSound("Data/Sounds/Menu.wav");
		m_musicBackground->PlaySound();
	
	// Button link
	texture = ResourceManagers::GetInstance()->GetTexture("btn_link.png");
	std::shared_ptr<MouseButton> btnLink = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnLink->Set2DPosition((SCREEN_WIDTH - btnLink->GetWidth()) / 2, SCREEN_HEIDHT / 2 );
	btnLink->SetSize(100, 100);
	btnLink->SetOnClick([this]() {
		m_soundEffectClick->PlaySfx(0);
		});
	m_listButton.push_back(btnLink);

	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	// Play sound effects
	m_soundEffectClick->PlaySfx(0);

	m_KeyPress = 0;

}

void GSOption::Exit()
{
	m_musicBackground->StopSound();
}


void GSOption::Pause()
{
	m_musicBackground->PauseSound();
}
void GSOption::Resume()
{
	if (m_isMusicOn) {
		m_musicBackground->PlaySound();
	}
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
			if (button == btnMusic)
			{
				
			}
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
