#include "collision.h"
#include "GSPlay.h"

Collision* Collision::s_Instance = nullptr;


Collision::Collision() : m_CollisionLayer(nullptr) {
    m_CollisionLayer = (TileLayer*)GSPlay::GetInstance()->GetMap()->GetMapLayers().back();
    m_CollisionTilemap = m_CollisionLayer->GetTilemap();
}

Collision* Collision::GetInstance() {
    if (!s_Instance) {
        s_Instance = new Collision();
    }
    return s_Instance;
}


bool Collision::CheckCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
   
    if (rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y) {
        return true; 
    }
    return false; 
}

bool Collision::MapCollision(SDL_Rect a) {
    int tilesSize = 32;
    int RowCount = 17;
    int ColCount = 89;

    int left_tile = a.x / tilesSize;
    int right_tile = (a.x + a.w) / tilesSize;

    int top_tile = a.y / tilesSize;
    int bottom_tile = (a.y + a.h) / tilesSize;

    if (left_tile < 0) left_tile = 0;
    if (right_tile > ColCount) right_tile = ColCount;

    if (top_tile < 0) top_tile = 0;
    if (bottom_tile > RowCount)bottom_tile = RowCount;

    for (int i = left_tile; i <= right_tile; ++i) {
        for (int j = top_tile; j <= bottom_tile; ++j) {
            if (m_CollisionTilemap[j][i] > 0) {
                return true;
            }
        }
    }
    return false;
}
void Collision::SetPlayer(Player* player) {
    m_Player = player;
}

void Collision::Update() {
    if (m_Player) {

        if (MapCollision(m_Player->GetRect())) {

            printf("Player has collided with the map!");
        }
    }
}