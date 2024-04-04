#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
class Sprite2D;
class SpriteAnimation;

class GSOption :
	public GameStateBase
{
public:
	GSOption();
	~GSOption();

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
	std::shared_ptr<MouseButton> button;
	std::shared_ptr<MouseButton> btnMusic;
	std::vector<std::shared_ptr<SpriteAnimation>> m_listAnimation;
	std::vector<std::shared_ptr<MouseButton>> m_listButton;
	std::shared_ptr<Sound> m_musicBackground;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<Sound> m_soundEffectClick;

	bool m_isMusicOn=true;
	float time = 0.0f;
	float m_Velocity = 10.0f;
};

