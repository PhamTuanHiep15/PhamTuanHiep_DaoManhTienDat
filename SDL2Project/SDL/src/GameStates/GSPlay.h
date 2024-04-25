#pragma once
#include "GameStateBase.h"
#include "GameObject/MouseButton.h"
#include "Sound.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "GameMap.h"
#include "Text.h"
class Sprite2D;
class SpriteAnimation;
class player;

class GSPlay :
    public GameStateBase
{
public:
    GSPlay();
    ~GSPlay();
    inline GameMap* GetMap() { return m_LevelMap; }
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


    GameMap* m_LevelMap;
    static GSPlay* GetInstance() {
        if (s_Instance == nullptr) {
            s_Instance = new GSPlay();
        }
        return s_Instance;
    }



private:
    std::shared_ptr<Sprite2D>	m_background;
    std::shared_ptr<Sprite2D>   m_ground;
    //std::shared_ptr<Text>		m_score;
    std::list<std::shared_ptr<MouseButton>>	m_listButton;


    std::shared_ptr<MouseButton> button;
    std::shared_ptr<Sound> m_soundEffectOnClick;


    std::list<std::shared_ptr<Player>>	m_listPlayer;
    std::shared_ptr<Player> m_player;

    std::list<std::shared_ptr<Item>>  m_listItemAnimation;
    std::shared_ptr<Item> chest, coin, book, coin1, coin2;

    std::list<std::shared_ptr<Enemy>>  m_listEnemyAnimation;
    std::shared_ptr<Enemy> dino, dino1, snake, snake1, snake2, slime, slime1;

    std::list<std::shared_ptr<Text>> m_listText;
    std::shared_ptr<Text>					m_textItem, m_GameOver;
    SDL_Color m_textColor;

    float time = 0.0f;
    float m_Velocity = 10.0f;
    SDL_Rect StaminaBar;
    static GSPlay* s_Instance;
    int n_Item = 0;
    bool gameRunning = true;
};

