#pragma once
#include <SDL_rect.h>
#include "Player.h"
#include "Item.h"
#include <vector>
#include "TileLayer.h"
#include "GameMap.h"
#include "Singleton.h"
class Collision /*: public CSingleton<Collision>*/  {
public:
    static Collision* GetInstance();
    bool MapCollision(SDL_Rect a);
    static bool CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
    void SetPlayer(Player* player);
    void Update();
private:
    Collision();
    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;
    Player* m_Player;
    static Collision* s_Instance;
};