#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"

GSOption::GSOption()
{
	m_soundEffectOn.LoadSfx("Data/Sounds/Alarm01.wav");
	m_soundEffectOff.LoadSfx("Data/Sounds/1.mp3");
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
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//sfx game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.png");
	btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->SetSize(100, 100);
	btnMusic->Set2DPosition((SCREEN_WIDTH - btnMusic->GetWidth()) / 2, SCREEN_HEIDHT / 2 -170);
	btnMusic->SetOnClick([]() {
		});
	m_listButton.push_back(btnMusic);
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
	*/

	bool isMusicOn = true;
	auto texture_music_on = ResourceManagers::GetInstance()->GetTexture("btn_sfx.png");
	auto texture_music_off = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");
	std::shared_ptr<MouseButton> btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnMusic->SetSize(100, 100);
	btnMusic->Set2DPosition((SCREEN_WIDTH - btnMusic->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 170);
	btnMusic->SetOnClick([this, btnMusic, texture_music_on, texture_music_off, isMusicOn]() mutable {
		if (isMusicOn) {
			btnMusic->SetTexture(texture_music_off);
			this->Pause();
		}
		else {
			btnMusic->SetTexture(texture_music_on);
			this->Resume();
		}
		isMusicOn = !isMusicOn;
		});
	m_listButton.push_back(btnMusic);
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
	
	//link game
	texture = ResourceManagers::GetInstance()->GetTexture("btn_link.png");
	std::shared_ptr<MouseButton> btnLink = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
	btnLink->Set2DPosition((SCREEN_WIDTH - btnLink->GetWidth()) / 2, SCREEN_HEIDHT / 2 );
	btnLink->SetSize(100, 100);
	btnLink->SetOnClick([]() {
		});
	m_listButton.push_back(btnLink);
	//Camera::GetInstance()->SetTarget(obj);
	m_listAnimation.push_back(obj);

	// Play sound effects
	m_soundEffectOn.PlaySfx(0); // Phát âm thanh khi trạng thái được khởi tạo
	m_soundEffectOff.PlaySfx(0);

	m_KeyPress = 0;

}

void GSOption::Exit()
{
}


void GSOption::Pause()
{
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/Alarm01.wav");
	m_Sound->PauseSound();
}
void GSOption::Resume()
{
	m_Sound = std::make_shared<Sound>();
	m_Sound->LoadSound("Data/Sounds/Alarm01.wav");
	m_Sound->PlaySound();
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
			if (button == btnMusic)
			{	
				m_isSoundOn = !m_isSoundOn;
				if (m_isSoundOn)
					m_soundEffectOff.PlaySfx(0); // Tắt âm thanh
				else
					m_soundEffectOn.PlaySfx(0); // Bật âm thanh
				m_isSoundOn = !m_isSoundOn; // Cập nhật trạng thái
				break;
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
