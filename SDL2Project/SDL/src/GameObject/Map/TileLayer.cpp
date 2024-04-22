#include "TileLayer.h"
#include"TextureManager.h"
#include "Camera.h"


TileLayer::TileLayer(int tilesize, int colcount, int rowcount, TileMap tilemap, TilesetList tilesets):
    m_TileSize(tilesize),m_ColCount(colcount),m_RowCount(rowcount),m_Tilemap(tilemap),m_Tilesets(tilesets) {

    
    for (unsigned int i = 0; i < m_Tilesets.size(); i++) {
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "Data/Map/" + m_Tilesets[i].Source);
    }

}

void TileLayer::Render() {
    for (unsigned int i = 0; i < m_ColCount; i++) {
        for (unsigned int j = 0; j < m_RowCount; j++) {
            int tileID = m_Tilemap[i][j];

            if (tileID == 0) continue;
            else
            {
                int index=0;
                if (m_Tilesets.size() > 1) {
                    for (unsigned int k = 1; k < m_Tilesets.size(); k++) {
                        if (tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID) {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                Tileset ts = m_Tilesets[index];
                int tileRow = ((tileID-1) % ts.ColCount)* ts.TileSize;
                int tileCol = ((tileID-1) / ts.ColCount) * ts.TileSize;
                TextureManager::GetInstance()->RenderTile(ts.Name, ts.TileSize, tileRow, tileCol, j * ts.TileSize, i * ts.TileSize, 1, SDL_FLIP_NONE);
                printf("%d %d\n",tileRow/ ts.TileSize,tileCol/ ts.TileSize);
            }
        }
    }
}
void TileLayer::Update() {
}
