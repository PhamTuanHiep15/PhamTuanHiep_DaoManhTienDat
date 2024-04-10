﻿#include "GSOption.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"
#include "Sound.h"
#include "MusicManager.h"


GSOption::GSOption() : m_soundEffectClick(std::make_shared<Sound>())
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
    texture = ResourceManagers::GetInstance()->GetTexture("btn_music.png");
    btnMusic = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnMusic->SetSize(150, 150);
    btnMusic->Set2DPosition((SCREEN_WIDTH - btnMusic->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 150);
    btnMusic->SetOnClick([this]() {
        });
    m_listButton.push_back(btnMusic);
    // Button SFX
    texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.png");
    std::shared_ptr<MouseButton> btnSfx = std::make_shared<MouseButton>(texture, SDL_FLIP_NONE);
    btnSfx->SetSize(150, 150);
    btnSfx->Set2DPosition((SCREEN_WIDTH - btnSfx->GetWidth()) / 2 , SCREEN_HEIDHT / 2 );
    btnSfx->SetOnClick([this]() {
        m_soundEffectClick->PlaySfx(0);
        });
    m_listButton.push_back(btnSfx);

    //Camera::GetInstance()->SetTarget(obj);
    m_listAnimation.push_back(obj);

    // Play sound effects
    m_soundEffectClick->PlaySfx(0);

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
                // Toggle music state
                m_soundEffectClick->PlaySfx(0);
                m_isMusicOn = !m_isMusicOn;
                if (m_isMusicOn) {
                    btnMusic->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_on.png"));
                }
                else {
                    btnMusic->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_music_off.png"));
                }

                // Toggle music state in MusicManager
                MusicManager musicManager;
                musicManager.toggleMusic(m_isMusicOn);
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