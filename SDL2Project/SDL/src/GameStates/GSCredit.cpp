#include "GSCredit.h"
#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/MouseButton.h"
#include "GameObject/SpriteAnimation.h"
#include "GameObject/Camera.h"
#include "KeyState.h"

GSCredit::GSCredit()
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
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

    //Set Font
    m_textColor = { 255, 255, 255 };
    m_textColor1 = { 0, 0, 0 };
    m_textGameName = std::make_shared<Text>("Data/gamera.ttf", m_textColor);
    m_textGameName->SetSize(450, 75);
    m_textGameName->Set2DPosition((SCREEN_WIDTH - m_textGameName->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 180);
    m_textGameName->LoadFromRenderText("ADVENTURE");
    m_Info1 = std::make_shared<Text>("Data/info1.otf", m_textColor1);
    m_Info1->SetSize(425, 50);
    m_Info1->Set2DPosition((SCREEN_WIDTH - m_Info1->GetWidth()) / 2, SCREEN_HEIDHT / 2 + 50);
    m_Info1->LoadFromRenderText("Dao Manh Tien Dat");
    m_Info2 = std::make_shared<Text>("Data/info1.otf", m_textColor1);
    m_Info2->SetSize(350, 50);
    m_Info2->Set2DPosition((SCREEN_WIDTH - m_Info2->GetWidth()) / 2, SCREEN_HEIDHT / 2 - 25);
    m_Info2->LoadFromRenderText("Pham Tuan Hiep");

    //Camera::GetInstance()->SetTarget(obj);
    m_listAnimation.push_back(obj);

    m_KeyPress = 0;

}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{
}
void GSCredit::Resume()
{
}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(SDL_Event& e)
{
}

void GSCredit::HandleTouchEvents(SDL_Event& e)
{
    for (auto button : m_listButton)
    {
        if (button->HandleTouchEvent(&e))
        {
            break;
        }
    }
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
    // Key State event

    for (auto it : m_listButton)
    {
        it->Update(deltaTime);
    }

}

void GSCredit::Draw(SDL_Renderer* renderer)
{
    m_background->Draw(renderer);
    //m_score->Draw();
    for (auto it : m_listButton)
    {
        it->Draw(renderer);
    }
    m_textGameName->Draw(renderer);
    m_Info1->Draw(renderer);
    m_Info2->Draw(renderer);
}