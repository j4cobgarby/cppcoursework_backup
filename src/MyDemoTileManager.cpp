#include "header.h"
#include "TileManager.h"
#include "MyDemoTileManager.hpp"

Psyjg12TileManager::Psyjg12TileManager() : TileManager(50, 50) {
    setMapSize(TILESY, TILESX);
    setTopLeftPositionOnScreen(0, 0);

    for (int i = 0; i < TILESX * TILESY; i++) {
        tiles_flipped[i] = rand() % 2;
    }
}

void Psyjg12TileManager::virtDrawTileAt(BaseEngine *eng, DrawingSurface *surf, int x, int y, int sx, int sy) const {
    bool f = tiles_flipped[y*TILESX+x];
    surf->drawRectangle(sx, sy, sx+50, sy+50, 0x000000);
    surf->drawLine(f ? sx : sx+50, sy, f ? sx+50 : sx, sy + 50, 0xffffff);
}

void Psyjg12TileManager::flipTile(int x, int y) {
    tiles_flipped[y*TILESX+x] = !tiles_flipped[y*TILESX+x];
}