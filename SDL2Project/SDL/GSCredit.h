#pragma once
#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include"GameObject/Text.h"
#include "Sound.h"
class Sprite2D;
class SpriteAnimation;

class GSCredit :
	public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(SDL_Event& e) override;
	void	HandleTouchEvents(SDL_Event& e) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw(SDL_Renderer* renderer) override;
	int m_KeyPress;

private:
	std::shared_ptr<Sprite2D>	m_background;
	//std::shared_ptr<Text>		m_score;
	std::list<std::shared_ptr<MouseButton>>	m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<Text>					m_textGameName,m_Info1,m_Info2;
	SDL_Color m_textColor,m_textColor1;
	std::shared_ptr<Sound>					m_musicBackground, m_soundEffectOnClick;
	std::shared_ptr<MouseButton> button;

	float time = 0.0f;
	float m_Velocity = 10.0f;
};

